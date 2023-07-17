#include "first_pass.h"
#include "includes.h"
#include "utils.h"
#include "globals.h"
#include "symbol_table.h"
#include "parse_line.h"

void first_pass(char *ifp)
{
    char *line = (char*)malloc(sizeof(char)*MAX_LINE);
    char *token = NULL;
    char *input_file_name = str_allocate_cat(ifp, ".am");
    FILE *input_file_des = fopen(input_file_name,"r");
    if (input_file_des == NULL) {
        printf("Error occurred while opening the file %s\n", input_file_name);
        free(input_file_name);
        return;
    }
    symbol *head, *curr;
    int IC = IC_START, DC = 0,L = 0;
    int i;
    char* command;
    char* first;
    char* second;
    int command_code;
    command = (char*)malloc(sizeof(char)*MAX_LEN);
    while (fgets(line,MAX_LINE,input_file_des) != NULL)
    {
        i = 0; L = 0;
        token = strtok(line," ");
        strcpy(command,token);
        command_code = opcode_no(command);
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
            continue;
        }
        if (strchr(token,':') != NULL) {
            token[strlen(token)-1] = '\0';
            if (isValid_macro(token) == 0) {
                curr = add_symbol(&head, token, IC);
            }
            else
            {
                fprintf(stderr,"ERROR: INVALID LABEL NAME");
                exit(1);
            }
            token = strtok(NULL," ");
            command_code = opcode_no(token);
            if (command_code >= 0 && command_code<=15){
                set_type(curr,ic);
                curr->opcode = command_code;
                goto check_opcode;
            }

            if (strcspn(token,".") == 0) {
                if (strcmp(token,".data") == 0)
                {
                    set_type(curr,data);
                    while (token != NULL) {
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            curr->nums[i] = atoi(token);
                            i++;
                            DC++;
                        }
                    }
                    curr->DC = DC;
                    curr->label_pos = curr->label_pos+=DC;
                    print_num_arr(curr);
                    continue;
                }
                if (strcmp(token,".string") == 0)
                {
                    set_type(curr,string);
                    token = strtok(NULL,"\"“”");
                    if (token!=NULL) {
                        if (token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
                        set_str(curr,token);
                        print_arr(curr->str);
                        DC = (int)strlen(token)+1;
                        L += DC;
                    }
                    curr->DC=DC;
                    continue;

                }
            }
            continue;
        }

        if(command_valid(command) == 0)
        {
            check_opcode:
            if(number_of_operands(command_code) == 2){
                first = strtok(NULL,",");
                second = strtok(NULL," ");
                if (second!=NULL) remove_newline(second);
                printf("opcode: %s first: %s second: %s\n",opcode_string(command_code),first,second);
                if (is_register(first))
                    if (is_register(second))
                        L+=2;
                L+=3;
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
