#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

/*** HEADER FILES  ***/
#include "globals.h"
#include "memory.h"
/*** HEADER FILES  ***/

typedef struct symbol{
    char label[MAX_LABEL];
    int label_pos;
    int type;
    int DC;
    char str[MAX_STR];
    struct symbol *next;
}symbol;
/*
 * create_symbol function creates a new symbol table based on a LinkedList.
 */
symbol *create_symbol(void);
/*
 * set_symbol function set values to a node *sym in a symbol table.
 */
void set_symbol(symbol *sym,char *name,int pos);
/*
 * set_type function sets the type of node *sym.
 */
void set_type(symbol *sym, TYPE type);
/*
 * set_type function sets the str field in a node *sym.
 */
void set_str(symbol *sym, char* str);
/*
 * add_symbol function adds a node to the symbol table.
 */
symbol* add_symbol(symbol **head, char *label, int pos);
/*
 * get_symbol function returns the corresponding node from the symbol table.
 */
int get_symbol(symbol *node,char* name);
/*
 * delete_symbol function deletes the given node from the symbol table.
 */
void delete_symbol(symbol **head, symbol *removed);
/*
 * get_DC function returns the DC field of the given node.
 */
int get_DC(symbol *head);
/*
 * free_symbol function deletes the symbol table and free the allocated memory assigned to it.
 */
void free_symbol(symbol *head);

#endif

