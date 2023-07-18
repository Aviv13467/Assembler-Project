#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "LinkedList.h"
#include "symbol_table.h"
#include "entry_table.h"
#include "extern_table.h"
void second_pass(char* ifp, node *head, symbol *label, entry_table *entry);

#endif
