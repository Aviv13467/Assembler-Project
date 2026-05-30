#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/*** HEADER FILES  ***/
#include "symbol_table.h"
/*** HEADER FILES  ***/

/*
 * second_pass is the second assembler pass that write missing addresses locations for labels
 */
void second_pass(char* ifp, node *head, symbol *label, entry_table *entry);

#endif
