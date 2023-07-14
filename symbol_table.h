#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct symbol{
    char label[31];
    int label_pos;
    struct symbol *next;
}symbol;
#endif
symbol *create_symbol(void);
void set_symbol(symbol *sym,char *name,unsigned int pos);
void add_symbol(symbol **head, char *label, unsigned int pos);
void print_symbol(symbol *head);
int get_symbol(symbol *node,char* name);
void free_symbol(symbol *head);