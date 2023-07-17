#include "first_pass.h"
#include "includes.h"
#include "utils.h"
#include "globals.h"
#include "symbol_table.h"
#include "parse_line.h"
#include "memory.h"

void first_pass(char *ifp)
{
    /*
     * Opening the preprocessed file .am to start the first assembler pass
     */
    char *input_file_name = str_allocate_cat(ifp, ".am");
    FILE *input_file_des = fopen(input_file_name,"r");
    /*
     * Opening failed, output an error
     */
    if (input_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", input_file_name);
        free(input_file_name);
        return;
    }
    char *line = (char*)malloc(sizeof(char)*MAX_LINE); /* line output from fgets */
    char *token = NULL; /* for strtok function */
    symbol *head, *curr; /* symbol table nodes */
    int IC = IC_START, DC = 0,L = 0, i,j,counter = 0; /* Insructcion counter, Data counter and Lines  counter (how many lines for each word of code) and 'i' index for later in the code*/
    char* first, *second; /* commands will be tokenized into 2 separate words */
    int command_code; /* opcode command (1-15) */
    char* command; /* command name string*/

    command = (char*)malloc(sizeof(char)*MAX_LEN); /* Allocating memory for the command char* ptr*/
    if (command == NULL){
        fprintf(stderr,"ALLOCATION FAILED");
        free(command);
        exit(1);
    }
    /*
     * The main loop in this function, parses each line in the .am file
     */

    while (fgets(line,MAX_LINE,input_file_des) != NULL) /* As long line != EOF */
    {
        counter++;
        i = 0; L = 0; /* Reset IC and 'i' */
        token = strtok(line," "); /* Tokenize the next word */
        strcpy(command,token); /* Copy token into command, so it won't interfere with the token pointer itself */
        command_code = opcode_no(command); /* Assign an integer value (opcode) to the command */

        /*
         * Check for .entry or .extern commands
         */
        if (strchr(token,'.') != NULL)
        {
            if (strcmp(token,".entry") == 0){
                token = strtok(NULL," ");
                token[strlen(token)-1] = '\0';
                if (isValid_macro(token) == 0) {
                    curr = add_symbol(&head, token, IC);
                    set_type(curr,entry);
                }
                continue;
            }
            else if (strcmp(token,".extern") == 0){
                token = strtok(NULL," ");
                token[strlen(token)-1] = '\0';
                if (isValid_macro(token) == 0) {
                    curr = add_symbol(&head, token, IC);
                    set_type(curr,ext);
                }
                continue;
            }
        }

        /*
         * Check for label word
         */

        if (strchr(token,':') != NULL) {
            token[strlen(token)-1] = '\0';
            /* Checks if the name is valid, in other words, if it doesn't interfere with known commands such as opcodes,registers or label types */
            if (isValid_macro(token) == 0) {
                curr = add_symbol(&head, token, IC);
            }
            /*
             * Name interferes with known command, output an error
             */
            else
            {
                fprintf(stderr,"ERROR line %d: INVALID LABEL NAME\n", counter);
            }

            /*
             * If no .entry/.extern, then it's a command within a label (for e.g. END: stop)
             */
            token = strtok(NULL," "); /* Tokenize the command */
            command_code = opcode_no(token); /* Assign integer number to the opcode (1-15) */

            /*
             * Checks whether it's a legal opcode
             */
            if (command_code >= 0 && command_code<=15){
                set_type(curr,ic);
                curr->opcode = command_code;
                goto check_opcode; /* goto the command parsing section */
            }

            /*
             * Check if it's a .data label
             */

            if (strcspn(token,".") == 0) {
                if (strcmp(token,".data") == 0)
                {
                    set_type(curr,data);
                    while (token != NULL) {
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            curr->nums[i] = atoi(token);
                            i++;
                        }
                        DC = i;
                    }
                    curr->DC = DC;
                    IC += DC;
                    print_num_arr(curr);
                    continue;
                }

                /*
                 * Checks if it's a .string label
                 */

                if (strcmp(token,".string") == 0)
                {
                    set_type(curr,string);
                    token = strtok(NULL,"\"“”");
                    if (token!=NULL) {
                        if (token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
                        set_str(curr,token);
                        print_arr(curr->str);
                        DC = (int)strlen(token)+1;
                        L = DC;
                        IC += L;
                        curr->DC=DC;
                    }
                    continue;
                }
            }
            continue; /* No more options, need to read a new line */
        }

        /*
         * Command parsing section
         */

        if(command_valid(command) == 0)
        {
            j = 0;
            check_opcode:
            if(number_of_operands(command_code) == 2){
                first = strtok(NULL,",");
                second = strtok(NULL," ");
                if (second!=NULL) remove_newline(second);
                printf("opcode: %s first: %s second: %s\n",opcode_string(command_code),first,second);
                /*
                 * Check if origin and destination operand are both registers that share a single code.
                 */
                switch (command_code) {
                    case mov:
                    case cmp:
                        if (isDigit(remove_newline(second)))
                            fprintf(stderr,"ERROR line: %d, 'mov' destination operand can't be a number\n",counter);
                    case add:
                    case sub:
                    {
                        if (isRegister(first) == 1) {

                            if (isRegister(second) == 1) {
                                curr->code[0] = encode_combine(command_code,DIRECT_REGISTER,DIRECT_REGISTER);
                                curr->code[1] = encode_combine_reg(register_no(first), register_no(second));
                                L += 2; /* Only need to add 2 lines, one for the command and one for the operands*/
                            }
                        }
                        else L+=3; /* else, needs additional lines for the destination operand*/
                    }
                        break;
                    case lea:
                    {
                        if (isRegister(first) || isDigit(first)) fprintf(stderr,"ERROR line: %d, origin operand of lea needs to be a label\n",counter);
                        L+=2;
                        if (!isRegister(second) && !isDigit(second)) { /* then it's a label */
                            curr->code[0] = encode_combine(lea,DIRECT,DIRECT);
                            curr->code[1] = 0; /* Only in the second pass we can assign address to a label */
                            curr->code[2] = 0; /* Only in the second pass we can assign address to a label */
                        }
                    }
                    break;
                }
            }
            else if(number_of_operands(command_code) == 1){
                first = strtok(NULL,",");
                if (first!=NULL) remove_newline(first);
                printf("opcode: %s first: %s\n",opcode_string(command_code),first);
                L+=2;
            }
            else if(number_of_operands(command_code) == 0){
                printf("opcode: %s \n",opcode_string(command_code));
                L+=1;
            }
            IC += L;
            continue;
        }
    }

    print_symbol(head);
    free(line);
    free(command);
    fclose(input_file_des);
    free(input_file_name);
}
