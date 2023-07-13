#include "includes.h"
typedef struct symbol{
    char label[MAX_LABEL];
    unsigned int label_pos;
    struct symbol *next;
}symbol;

symbol *create_symbol(void);
void set_symbol(symbol *sym,char *name,unsigned int pos);
void add_symbol(symbol **head, char *label, unsigned int pos);
void print_symbol(symbol *head);
void free_symbol(symbol *head);