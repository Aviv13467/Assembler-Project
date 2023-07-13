#include "symbol_table.h"
#include "includes.h"
symbol *create_symbol(void)
{
    symbol *new;
    new = (symbol*) malloc(sizeof(symbol));
    if(new == NULL)
        exit(1);
    else return new;
}
void set_symbol(symbol *sym,char *name,unsigned int pos)
{
    strcpy(sym->label,name);
    sym->label_pos = pos;
}
void add_symbol(symbol **head, char *label, unsigned int pos)
{
    symbol *new = create_symbol();
    set_symbol(new,label,pos);
    new->next = NULL;
    struct symbol *curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new;
}
void print_symbol(symbol *head)
{
    symbol *curr = head;
    while (curr!= NULL)
    {
        printf("%s\t%d\n", curr->label, curr->label_pos);
        curr = curr->next;
    }
}
void free_symbol(symbol *head) {
    symbol* curr = head;
    while (curr != NULL) {
        symbol* temp = curr;
        curr = curr->next;
        free(temp);
    }
}