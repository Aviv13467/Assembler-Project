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
    symbol *head;
    int count = IC_START;
    int IC,DC = 0;

    while (fgets(line,MAX_LINE,input_file_des) != NULL)
    {
        token = strtok(line," ");
        if (strchr(token,':') != NULL) {
            token[strlen(token)-1] = '\0';
            add_symbol(&head, token, count);
        }
        /*
         * Continue from here: Last edited 15/07/2023 00:00, I want to implement parsing of lines to the corresponding commands.
        token = strtok(NULL," ");
         */
    }
    /*
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
     */
    print_symbol(head);
    free(line);
    fclose(input_file_des);
    free(input_file_name);
}