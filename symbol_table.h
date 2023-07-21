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
    int IC;
    int nums[30];
    char str[30];
    struct symbol *next;
}symbol;

symbol *create_symbol(void);
void set_symbol(symbol *sym,char *name,unsigned int pos);
void set_type(symbol *sym, TYPE type);
void set_str(symbol *sym, char* str);
void set_IC(symbol *sym,int IC);
void set_DC(symbol *sym,int DC);
symbol* add_symbol(symbol **head, char *label, unsigned int pos);
int print_symbol(symbol *head);
int get_symbol(symbol *node,char* name);
symbol *get_actual_symbol(symbol *head, char* name);
void delete_symbol(symbol **head, symbol *removed);
void print_num_arr(symbol *curr);
void print_entry(symbol *head);
void print_extern(symbol *head);
int get_DC(symbol *head);
void free_symbol(symbol *head);

#endif