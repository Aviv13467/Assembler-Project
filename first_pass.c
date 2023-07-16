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
    int count = IC_START;
    int IC = 0, DC = 0,L = 0;
    int i = 0;
    while (fgets(line,MAX_LINE,input_file_des) != NULL)
    {
        i = 0, DC = 0;
        token = strtok(line," ");
        if (strchr(token,':') != NULL) {
            token[strlen(token)-1] = '\0';
            curr = add_symbol(&head, token, L+count);
            token = strtok(NULL," ");
            if (strcspn(token,".") == 0) {
                if (strcmp(token,".data") == 0)
                {
                    while (token != NULL) {
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            curr->nums[i] = atoi(token);
                            i++;
                            DC++;
                        }
                    }
                    L += DC;
                    curr->DC = DC;
                    continue;
                }
                if (strcmp(token,".string") == 0)
                {
                    token = strtok(NULL," \"“”");
                    if (token!=NULL) {
                        if (token[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
                        set_str(curr,token);
                        DC = (int)strlen(token)+1;
                        L += DC;
                    }
                    curr->DC=DC;
                    continue;

                }
            }

        }
    }

    print_symbol(head);
    free(line);
    fclose(input_file_des);
    free(input_file_name);
}
