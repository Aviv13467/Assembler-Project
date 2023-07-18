#include "preprocessor.h"
#include "first_pass.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i <argc; ++i) {
        preproces_file(argv[i]);
        if(preproces_file(argv[i]) == 0) {
            fprintf(stdout,"***** PREPROCESSOR SUCCESS *****\n");
            first_pass(argv[i]);
            if(first_pass(argv[i]) == 0)
                fprintf(stdout,"***** ASSEMBLER SUCCESS *****\n");
            else
                fprintf(stderr,"***** ASSEMBLER FAILED *****\n");
        }
        else
            fprintf(stderr,"***** PREPROCESSOR FAILED *****\n");
    }
    return 0;
}