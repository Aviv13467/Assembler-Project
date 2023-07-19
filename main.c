#include "preprocessor.h"
#include "first_pass.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i <argc; ++i) {
        preproces_file(argv[i]);
        if(preproces_file(argv[i]) == 0) {
            fprintf(stdout,"***** PREPROCESSOR SUCCESS for %s *****\n",argv[i]);
            first_pass(argv[i]);
            if(first_pass(argv[i]) == 0)
                fprintf(stdout,"***** ASSEMBLER SUCCESS for %s *****\n",argv[i]);
            else
                fprintf(stderr,"***** ASSEMBLER FAILED for %s *****\n",argv[i]);
        }
        else
            fprintf(stderr,"***** PREPROCESSOR FAILED for %s *****\n",argv[i]);
    }
    return 0;
}