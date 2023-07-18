#include "second_pass.h"
#include "includes.h"
#include "utils.h"
#include "LinkedList.h"

void second_pass(char *ifp)
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
}