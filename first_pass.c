#include "includes.h"
#include "utils.h"
#include "symbol_table.h"

void first_pass(char *ifp)
{
    char *line = (char*)malloc(sizeof(char)*MAX_LINE);
    char *token = NULL;
    unsigned int pos;
    char *input_file_name = str_allocate_cat(ifp, ".am");
    FILE *input_file_des = fopen(input_file_name,"r");
    if (input_file_des == NULL) {
        printf("Error occurred while opening the file %s\n", input_file_name);
        free(input_file_name);
        return;
    }
    symbol *head;
    int count;
    count = 100;
    while (fgets(line,MAX_LINE,input_file_des) != NULL)
    {
        if (strchr(line,':') == NULL) {
            count++;
            continue;
        }
        else
        {
            token = strtok(line, ":");
            flush_strtok();
            if (token != NULL) {
                add_symbol(&head, token, count);
            }
        }
        count++;
    }
    print_symbol(head);
    free(line);
    fclose(input_file_des);
    free(input_file_name);
}