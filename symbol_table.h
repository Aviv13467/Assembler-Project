#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "globals.h"
#include "includes.h"
#include "utils.h"
#include "memory.h"

typedef struct symbol{
    char label[31];
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
void print_num_arr(symbol *curr);
void print_entry(symbol *head);
void print_extern(symbol *head);
void free_symbol(symbol *head);
#endif