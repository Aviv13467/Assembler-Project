#ifndef FIRST_PASS_H
#define FIRST_PASS_H

/*** HEADER FILES  ***/
#include "utils.h"
#include "symbol_table.h"
#include "second_pass.h"
/*** HEADER FILES  ***/

/*** DEFINES ***/
#define error err_flag = 'Y';

int first_pass(char *ifp);

#endif
