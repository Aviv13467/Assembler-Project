#include "symbol_table.h"

symbol *create_symbol(void)
{
    symbol *new;
    new = (symbol*) malloc(sizeof(symbol));
    if(new == NULL)
        exit(1);
    else return new;
}
void set_symbol(symbol *sym,char *name,int pos)
{
    strcpy(sym->label,name);
    sym->label_pos = pos;
}
void set_type(symbol *sym, TYPE type)
{
    sym->type = type;
}

void set_str(symbol *sym, char* str)
{
    strcpy(sym->str,str);
}

symbol* add_symbol(symbol **head, char *label, int pos) {
    symbol *new = create_symbol();
    if (new == NULL)
        return NULL;

    set_symbol(new, label, pos);
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
    } else {
        symbol *curr = *head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new;
    }

    return new;
}

int get_symbol(symbol *node,char* name)
{
    symbol *curr = node;
    while (curr != NULL)
    {
        if (strcmp(curr->label,name)==0) {
            if (curr->type == ext) return -2;
            else return curr->label_pos;
        }
        curr = curr->next;
    }
    return -1;
}
void delete_symbol(symbol **head, symbol *removed)
{
    symbol *curr;
    curr = *head;
    if (*head == NULL || removed == NULL) return;
    if (*head == removed){
        *head = removed->next;
        free(removed);
        return;
    }
    while (curr->next != removed)
        curr = curr->next;
    curr->next = curr->next->next;
    if (curr->next == NULL) {
        return;
    }
    curr->next = removed->next;
    free(removed);
}
int get_DC(symbol *head)
{
    int sum = 0;
    symbol *curr = head;
    while (curr!=NULL)
    {
        sum+=curr->DC;
        curr = curr->next;
    }
    return sum;
}

void free_symbol(symbol *head)
{
    symbol *curr;
    if (head == NULL) return;
    curr = head;
    while (curr != NULL) {
        symbol* temp = curr;
        curr = curr->next;
        free(temp);
    }
}
