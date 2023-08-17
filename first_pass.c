#include "first_pass.h"

#define add_line line_info = add_node(&head_list,counter++,0);
int first_pass(char *ifp)
{
    /*
     * Opening the preprocessed file .am to start the first assembler pass
     */
    char *input_file_name = str_join(ifp, ".am");
    FILE *input_file_des = fopen(input_file_name,"r");
    char *line, *token, *tokencpy, *garbage;
    symbol *head,*curr;
    node *head_list;
    entry_table *head_entry;
    extern_table  *head_extern;
    int IC,DC,L,i,counter,line_count,num;
    char *first, *second, err_flag;
    int command_code; /* opcode command (1-15) */
    char* command; /* command name string*/
    node *line_info;
    int k;
    /*
     * Opening failed, output an error
     */
    if (input_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", input_file_name);
        free(input_file_name);
        exit(1);
    }
    line = (char*)malloc(sizeof(char)*MAX_LINE); /* line output from fgets */
    token = NULL, tokencpy = NULL, garbage = NULL; /* for strtok,strtol function */
    head = NULL, curr = NULL; /* symbol table nodes */
    head_list = NULL;

    head_entry = NULL;
    head_extern = NULL;

    IC = IC_START, DC = 0;
    counter = 0, line_count = 0; /* Instruction counter, Data counter and Lines  counter (how many lines for each word of code) and 'i' index for later in the code*/
    err_flag = 'N'; /* commands will be tokenized into 2 separate words */

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
        /*
         * Checks if there are more words than the imaginary PC with 1024 byte of memory can handle
         * If there are more bytes than 1024 a 'stackoverflow' error will end the program
         */
        if (counter>923){ /* 923 because the memory starts at 100 */
            fprintf(stderr,"ERROR, STACKOVERFLOW, OUT OF MEMORY. USED %d/%d\n",counter,1024);
            exit(1);
        }
        line_count++;
        line_info = add_node(&head_list,counter,0);
        counter++; /* Increment line counter used for error output */
        i = 0; L = 0; /* Reset command line counter and 'i' */
        token = strtok(line," "); /* Tokenize the next word */
        strcpy(command,token); /* Copy token into command, so it won't interfere with the token pointer itself */
        command_code = opcode_no(command); /* Assign an integer value (opcode) to the command */

        /*
         * Check for label word
         */

        if (strchr(token,':') != NULL) {
            token[strlen(token)-1] = '\0';

            /* Checks if the name is valid, in other words, if it doesn't interfere with known commands such as opcodes,registers or label types */
            if (isValid_label(token) == 0) {
                curr = add_symbol(&head, token, IC);
            }
            /*
             * Name interferes with known command, output an error
             */
            else
            {
                fprintf(stderr,"ERROR line %d: INVALID LABEL NAME\n", line_count);
                error
                continue;
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
                if (strcmp(token,".entry") == 0){
                    counter--;
                    token = strtok(NULL," ");
                    token[strlen(token)-1] = '\0';
                    if (strtok(NULL," ")){ /* Yield error, more than 1 argument */
                        fprintf(stderr,"ERROR in line %d: .entry expect only 1 argument\n",line_count);
                        error
                        continue;
                    }
                    if (isValid_label(token) == 0) {
                        add_entry(&head_entry,token,0);
                        delete_node(&head_list,line_info);
                    }
                    fprintf(stderr,"WARNING in line %d: label before .entry is redundant\n",line_count); /* Yield a warning, any label before .entry is not necessary  */
                    delete_symbol(&head,curr);
                }
                if (strcmp(token,".data") == 0) /* Handle .data */
                {
                    /* Since not a command, we'll delete the node and command counter used to track commands in my algorithm */
                    delete_node(&head_list,line_info);
                    counter--;
                    set_type(curr,data);

                    tokencpy = (char*)malloc(sizeof(char)* strlen(token));
                    strcpy(tokencpy,token);
                    tokencpy = strtok(NULL," ");
                    if (tokencpy[0] == ','){ /* Checks for illegal comma before argument */
                        fprintf(stderr,"ERROR in line %d: illegal comma before first argument\n",line_count);
                        error
                        continue;
                    }
                    if (comma_check(tokencpy) == 1){ /* Checks for illegal consecutive commas between or after arguments */
                        fprintf(stderr,"ERROR in line %d: two consecutive commas after an argument\n",line_count);
                        error
                        continue;
                    }
                    token = strtok(tokencpy,",");
                    while (token != NULL) {
                        if (token != NULL) {
                            add_line
                            num = (int)strtol(remove_newline(token),&garbage,10);
                            if (garbage[0] != '\0'){ /* Checks for illegal characters after .data */
                                fprintf(stderr,"ERROR in line %d: illegal argument, .data can only receive integers\n",line_count);
                                error
                                break;
                            }
                            if (num<0)
                                line_info->code = two_complement(atoi(token)); /* Need to send the binary  representation of a negative number using the two-complements method */
                            else line_info->code = atoi(token);
                            i++;
                        }
                        DC = i;
                        token = strtok(NULL, ",");
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
                        for (k = 0; k < strlen(token)+1 ; ++k) {
                            add_line
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
            else if (command_code == -1) {
                fprintf(stderr,"ERROR in line %d: ILLEGAL COMMAND NAME\n",line_count);
                error
                continue;
            }
            continue; /* No more options, need to read a new line */
        }

        /*
         * Check for .entry or .extern commands
         */
        if (strchr(token,'.') != NULL)
        {
            if (strcmp(token,".entry") == 0){ /* Handles .entry */
                counter--; /* Not a command */
                token = strtok(NULL," ");
                token[strlen(token)-1] = '\0';
                if (strtok(NULL," ")){
                    fprintf(stderr,"ERROR in line %d: .entry expect only 1 argument\n",line_count);
                    error
                    continue;
                }
                if (isValid_macro(token) == 0) {

                    /* curr = add_symbol(&head, token, 0); */
                    add_entry(&head_entry,token,0);
                    /* set_type(curr,entry); */
                    delete_node(&head_list,line_info);
                }
                continue;
            }
            else if (strcmp(token,".extern") == 0){ /* Handles .extern */
                counter--; /* Not a command */
                token = strtok(NULL," ");
                remove_newline(token);
                if (strtok(NULL," ")){
                    fprintf(stderr,"ERROR in line %d: .extern expect only 1 argument\n",line_count);
                    error
                    continue;
                }

                if (isValid_label(token) == 0) {
                    curr = add_symbol(&head, token, 0);
                    set_type(curr,ext);
                    add_extern(&head_extern,token,0);
                    delete_node(&head_list,line_info);
                }
                else {
                    fprintf(stderr,"ERROR IN LINE %d: INVALID .extern ARGUMENT\n",line_count);
                    error
                    continue;
                }
                continue;
            }
        }

        /*
         * Command parsing section
         */

        if(command_valid(command) == 0)
        {
            check_opcode:
            if(number_of_operands(command_code) == 2){
                first = strtok(NULL,",");
                removeLeadingWhitespaces(first);
                remove_whitespaces(first); /* Removes whitespaces in case there are */
                second = strtok(NULL," ");
                if (redundant_comma_check(second) == 1){
                    fprintf(stderr,"ERROR in line %d: redundant comma after a command\n",line_count);
                    error
                    continue;
                }
                if (first == NULL || second == NULL){
                    fprintf(stderr,"ERROR in line %d: '%s' is missing operands\n",line_count, opcode_string(command_code));
                    error
                    continue;
                }
                if (second!=NULL) remove_newline(second);
                if (strtok(NULL," ")){
                    fprintf(stderr,"ERROR in line %d: extraneous argument passed\n",line_count);
                    error
                    continue;
                }
                /*printf("opcode: %s first: %s second: %s\n",opcode_string(command_code),first,second);*/
                /*
                 * Check if origin and destination operand are both registers that share a single code.
                 */
                switch (command_code) {
                    case mov:
                        if (isDigit(remove_newline(second))) {
                            fprintf(stderr, "ERROR in line %d: 'mov' destination operand can't be a number\n",line_count);
                            error
                            continue;
                        }
                    case cmp:
                        if (isRegister(first) == 1) {
                            if (isDigit(second)){
                                line_info->code = encode_combine(command_code, DIRECT_REGISTER, DIRECT);
                                add_line
                                line_info->code = encode_origin_reg_direct(register_no(first));
                                add_line
                                if (atoi(second) < 0)
                                    line_info->code = two_complement(encode_absolute(atoi(second)));
                                else
                                    line_info->code = encode_absolute(atoi(second));
                                set_label(line_info,second);
                                L += 3;
                                continue;
                            }
                        }


                    case add:
                    case sub:
                    {
                        if (!isRegister(first) && first[0] == '@'){
                            fprintf(stderr,"ERROR in line %d: invalid register name\n",line_count);
                            error
                            continue;
                        }
                        if (!isRegister(second) && second[0] == '@'){
                            fprintf(stderr,"ERROR in line %d: invalid register name\n",line_count);
                            error
                            continue;
                        }
                        if (isRegister(first) == 1) {
                            if (isRegister(second) == 1) {
                                line_info->code = encode_combine(command_code,DIRECT_REGISTER,DIRECT_REGISTER);
                                add_line
                                line_info->code = encode_combine_reg(register_no(first), register_no(second));
                                L += 2; /* Only need to add 2 lines, one for the command and one for the operands*/
                            }
                            else if (isDigit(second)){
                                fprintf(stderr,"ERROR in line %d: invalid destination operand\n",line_count);
                                error
                                continue;
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
                            fprintf(stderr,"ERROR line %d:, origin operand of lea needs to be a label\n",line_count);
                            error
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
                    default:
                        continue;
                }
            }
            else if(number_of_operands(command_code) == 1){
                first = strtok(NULL,",");
                removeLeadingWhitespaces(first);
                if (first == NULL){
                    fprintf(stderr,"ERROR in line %d: '%s' is missing operands\n",line_count, opcode_string(command_code));
                    error
                    continue;
                }
                if (strtok(NULL,", ")){
                    fprintf(stderr,"ERROR in line %d: extraneous argument passed\n",line_count);
                    error
                    continue;
                }
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
                            fprintf(stderr,"ERROR in line %d: can't have immediate destination operand\n",line_count);
                            error
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
                                line_info->code = two_complement(encode_absolute((atoi(first))));
                            }
                            else
                                line_info->code = encode_absolute((atoi(first)));
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
                    default:
                        continue;
                }
            }
            else if(number_of_operands(command_code) == 0){
                if (strtok(NULL," ")){
                    fprintf(stderr,"ERROR in line %d: extraneous argument passed\n",line_count);
                    error
                    continue;
                }
                switch (command_code) {
                    case rts:
                    case stop:
                    {
                        if (redundant_comma_check(tokencpy) == 1){
                            fprintf(stderr,"ERROR in line %d: redundant comma after a command\n",line_count);
                            error
                            continue;
                        }
                        if (strtok(NULL,", ")){
                            fprintf(stderr,"ERROR in line %d: extraneous argument passed\n",line_count);
                            error
                            continue;
                        }
                        else
                            line_info->code = encode_combine(command_code,0,0);
                    }
                    default:;
                }
                L+=1;
            }
            IC += L;
            continue;
        }
        else
        {
            fprintf(stderr,"ERROR in line %d: ILLEGAL COMMAND\n",line_count);
            error
            continue;
        }

    }

    free(line);
    free(command);
    if (err_flag == 'N') second_pass(ifp,head_list,head,head_entry);
    else return 1;
    if (!tokencpy) free(tokencpy);
    free_symbol(head);
    free_list(head_list);
    free_entry(head_entry);
    fclose(input_file_des);
    free(input_file_name);

    return 0;
}
