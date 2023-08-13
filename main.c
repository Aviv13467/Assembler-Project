#include "preprocessor.h"
#include "first_pass.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
    int i, result_pre, result_first;
    for (i = 1; i <argc; ++i) {
        result_pre = preproces_file(argv[i]);
        if(result_pre == 0) {
            fprintf(stdout,"***** PREPROCESSOR SUCCESS for %s *****\n",argv[i]);
            result_first = first_pass(argv[i]);
            if(result_first == 0)
                fprintf(stdout,"***** ASSEMBLER SUCCESS for %s *****\n",argv[i]);
            else
                fprintf(stderr,"***** ASSEMBLER FAILED for %s *****\n",argv[i]);
        }
        else
            fprintf(stderr,"***** PREPROCESSOR FAILED for %s *****\n",argv[i]);
    }
    return 0;
}
