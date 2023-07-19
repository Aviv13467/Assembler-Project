#include "includes.h"
#include "utils.h"
#include "hashtable.h"

int preproces_file(char *ifp) {
    hash_table *ht = ht_create();
    int isMacro = 0;
    char *token = NULL;
    char *linecpy = (char*)malloc(sizeof(char)*MAX_LINE);
    char *macro_name = NULL;
    char line[MAX_LINE];
    char* copy;
    char *input_file_name = str_allocate_cat(ifp, ".as");
    char *output_file_name = str_allocate_cat(ifp, ".am");

    FILE *input_file_des = fopen(input_file_name, "r");

    /*
     * Opening failed, setting free the allocated memory
     */
    if (input_file_des == NULL) {
        printf("Error occurred while opening the file %s\n", input_file_name);
        free(input_file_name);
        free(output_file_name);
        ht_free(ht);
        exit(1);
    }

    /*
     * Opening of output file failed, setting free the allocated memory and closing the other files
     */
    FILE *am_file_des = fopen(output_file_name, "w+");
    if (am_file_des == NULL) {
        printf("Couldn't open a file named %s.am\n", output_file_name);
        free(output_file_name);
        free(input_file_name);
        fclose(input_file_des);
        fclose(am_file_des);
        ht_free(ht);
        exit(1);
    }

    while (fgets(line, MAX_LINE, input_file_des) != NULL) {
        strcpy(linecpy,line);
        if (line[0] == '\n' || line[0] == ';' || line[0] == EOF || line[0] == '\0')
            continue;
        if(isMacro == 1) {
            if (strcmp(token, "endmcro\n") == 0) {
                isMacro = 0;
                continue;
            }
            else{
                char *updated_macro = str_allocate_cat(ht_get(ht, macro_name), linecpy);
                ht_set(ht, macro_name, updated_macro);
                free(updated_macro);
                continue;
            }
        }
        token = strtok(line, " ");
        /*
         * Means there is a key, macro found. we'll print it to the file
         */
        if (ht_get(ht, token) != NULL) {
            fputs(ht_get(ht, token), am_file_des);
            continue;
        }
        /*
         * Check if the token is start of a macro
         */
        if (strcmp(token, "mcro") == 0) {
            isMacro = 1;
            macro_name = (char *) malloc(sizeof(char) * MAX_MCRO_LEN);
            strcpy(macro_name, strtok(NULL, " "));
            if (strtok(NULL," ") != NULL){
                fprintf(stderr,"ERROR: EXTRANEOUS TEXT AFTER MACRO");
                exit(1);
            }
            copy = (char*) malloc(sizeof(char) * strlen(macro_name));
            strcpy(copy,macro_name);
            copy[strlen(copy)-1]='\0';
            if (isValid_macro(copy) == 0) {
                ht_set(ht, macro_name, "");
                continue;
            }
            else {
                fprintf(stderr, "ERROR: INVALID MACRO NAME");
                exit(1);
            }
        }
        fputs(linecpy, am_file_des);
    }

    free(output_file_name);
    free(input_file_name);
    fclose(input_file_des);
    fclose(am_file_des);
    ht_free(ht);
    if (macro_name != NULL) free(macro_name);

    return 0;
}
