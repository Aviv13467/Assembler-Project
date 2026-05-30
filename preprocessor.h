#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

/*** HEADER FILES  ***/

#include "utils.h"
#include "hashtable.h"
#include "globals.h"
/*** HEADER FILES  ***/

/*
 * preprocess_file function is the first stage of the assembler program. It replaces macros with their content
 */
int preprocess_file(char *ifp);
#endif
