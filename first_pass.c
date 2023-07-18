#include "first_pass.h"
#include "includes.h"
#include "utils.h"
#include "globals.h"
#include "symbol_table.h"
#include "parse_line.h"
#include "memory.h"
#include "LinkedList.h"
#include "second_pass.h"

#define add_line line_info = add_node(&head_list,counter++,0);
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
    symbol *head = NULL, *curr = NULL; /* symbol table nodes */
    node *head_list = NULL;
    int IC = IC_START, DC = 0,L = 0, i = 0,counter = 0; /* Insructcion counter, Data counter and Lines  counter (how many lines for each word of code) and 'i' index for later in the code*/
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
        node *line_info = add_node(&head_list,counter,0);
        counter++; /* Increment line counter used for error output */
        i = 0; L = 0; /* Reset command line counter and 'i' */
        token = strtok(line," "); /* Tokenize the next word */
        strcpy(command,token); /* Copy token into command, so it won't interfere with the token pointer itself */
        command_code = opcode_no(command); /* Assign an integer value (opcode) to the command */

        /*
         * Check for .entry or .extern commands
         */
        if (strchr(token,'.') != NULL)
        {
            if (strcmp(token,".entry") == 0){
                counter--;
                token = strtok(NULL," ");
                token[strlen(token)-1] = '\0';
                if (isValid_macro(token) == 0) {
                    curr = add_symbol(&head, token, 0);
                    set_type(curr,entry);
                    delete_node(&head_list,line_info);
                }
                continue;
            }
            else if (strcmp(token,".extern") == 0){
                counter--;
                token = strtok(NULL," ");
                token[strlen(token)-1] = '\0';
                if (isValid_macro(token) == 0) {
                    curr = add_symbol(&head, token, 0);
                    set_type(curr,ext);
                    delete_node(&head_list,line_info);
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
                curr->IC = IC;
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
                goto check_opcode; /* goto the command parsing section */
            }

            /*
             * Check if it's a .data label
             */

            if (strcspn(token,".") == 0) {
                if (strcmp(token,".data") == 0)
                {
                    delete_node(&head_list,line_info);
                    counter--;
                    set_type(curr,data);
                    while (token != NULL) {
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            add_line
                            if (atoi(token)<0)
                                line_info->code = two_complement(atoi(token));
                            else line_info->code = atoi(token);
                            i++;
                        }
                        DC = i;
                    }
                    curr->DC = DC;
                    IC += DC;
                    /* print_num_arr(curr); */
                    continue;
                }

                /*
                 * Checks if it's a .string label
                 */

                if (strcmp(token,".string") == 0)
                {
                    delete_node(&head_list,line_info);
                    counter--;
                    set_type(curr,string);
                    token = strtok(NULL,"\"“”");
                    if (token!=NULL) {
                        if (token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
                        set_str(curr,token);
                        int k;
                        for (k = 0; k < strlen(token)+1 ; ++k) {
                            add_line;
                            line_info->code = (int)token[k];
                        }
                        /* print_arr(curr->str); */
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
            check_opcode:
            if(number_of_operands(command_code) == 2){
                first = strtok(NULL,",");
                second = strtok(NULL," ");
                if (second!=NULL) remove_newline(second);
                /*printf("opcode: %s first: %s second: %s\n",opcode_string(command_code),first,second);*/
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
                                line_info->code = encode_combine(command_code,DIRECT_REGISTER,DIRECT_REGISTER);
                                add_line
                                line_info->code = encode_combine_reg(register_no(first), register_no(second));
                                L += 2; /* Only need to add 2 lines, one for the command and one for the operands*/
                            }
                            else {
                                line_info->code = encode_combine(command_code, DIRECT_REGISTER, DIRECT);
                                add_line
                                line_info->code = encode_origin_reg_direct(register_no(first));
                                add_line
                                line_info->code = 0; /* Address will be added in second pass */
                                set_label(line_info,second);
                                L += 3;
                            }
                        }
                        else{ /* else, needs additional lines for the destination operand*/
                            add_line
                            L+=3;
                        }
                    }
                        break;
                    case lea:
                    {
                        if (isRegister(first) || isDigit(first)){
                            fprintf(stderr,"ERROR line: %d, origin operand of lea needs to be a label\n",counter);
                            L+=2;
                            break;
                        }
                        if (!isRegister(second) && !isDigit(second)) { /* then it's a label */
                            line_info->code = encode_combine(lea,DIRECT,DIRECT);
                            add_line
                            line_info->code = 0; /* Only in the second pass we can assign address to a label */
                            set_label(line_info,first);
                            add_line
                            line_info->code = 0; /* Only in the second pass we can assign address to a label */
                            set_label(line_info,second);
                        }
                        if (isRegister(second)){
                            line_info->code = encode_combine(lea,DIRECT,DIRECT_REGISTER);
                            add_line
                            line_info->code = 0; /* Only in the second pass we can assign address to a label */
                            set_label(line_info,first);
                            add_line
                            line_info->code = encode_des_reg_direct(register_no(second));
                        }
                    }
                    break;
                }
            }
            else if(number_of_operands(command_code) == 1){
                first = strtok(NULL,",");
                if (first!=NULL) remove_newline(first);
                switch (command_code) {
                    case not:
                    case clr:
                    case inc:
                    case dec:
                    case jmp:
                    case bne:
                    case red:
                    case jsr:
                    {
                        if (isDigit(first)){
                            fprintf(stderr,"ERROR line: %d %s can't have immediate destination operand",counter,first);
                            break;
                        }
                        if (!isRegister(first)){
                            line_info->code = encode_combine(command_code,0,DIRECT);
                            add_line
                            line_info->code = 0; /* Only in the second pass we can assign address to a label */
                            set_label(line_info,first);
                            L+=2;
                        }
                        else if (isRegister(first))
                        {
                            line_info->code = encode_combine(command_code,0,DIRECT_REGISTER);
                            add_line
                            line_info->code = encode_des_reg_direct(register_no(first));
                            L+=2;
                        }
                        break;
                    }
                    case prn:
                    {
                        if (isDigit(first))
                        {
                            line_info->code = encode_combine(command_code,0,IMMEDIATE);
                            add_line
                            if (atoi(first) < 0) {
                                line_info->code = two_complement(encode_immediate((atoi(first))));
                            }
                            else
                                line_info->code = encode_immediate((atoi(first)));
                            L+=2;
                            break;
                        }
                        if (!isRegister(first) && !isDigit(first)){
                            line_info->code = encode_combine(command_code,0,DIRECT);
                            add_line
                            line_info->code = 0; /* Only in the second pass we can assign address to a label */
                            set_label(line_info,first);
                            L+=2;
                        }
                        else if (isRegister(first))
                        {
                            line_info->code = encode_combine(command_code,0,DIRECT_REGISTER);
                            add_line
                            line_info->code = encode_des_reg_direct(register_no(first));
                            L+=2;
                        }
                        break;
                    }
                }
                /*printf("opcode: %s first: %s\n",opcode_string(command_code),first);*/
            }
            else if(number_of_operands(command_code) == 0){
                switch (command_code) {
                    case rts:
                    case stop:
                    {
                        line_info->code = encode_combine(command_code,0,0);
                    }

                }
                /*printf("opcode: %s \n",opcode_string(command_code));*/
                L+=1;
            }
            IC += L;
            continue;
        }
    }
    /*
    b64(head_list);
     */
    printf("LinkedList:\n");
    print_node(head_list);
    putchar('\n');
    int DC_total;
    DC_total = print_symbol(head);
    printf("%d %d",counter-DC_total,DC_total);
    print_entry(head);
    free(line);
    free(command);
    second_pass(head_list,head);
    print_node(head_list);
    b64(head_list);
    free_symbol(head);
    free_list(head_list);
    fclose(input_file_des);
    free(input_file_name);
}
