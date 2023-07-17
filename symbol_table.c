#include "symbol_table.h"
#include "includes.h"
#include "utils.h"
#include "memory.h"
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
void set_type(symbol *sym, TYPE type)
{
    sym->type = type;
}

void set_str(symbol *sym, char* str)
{
    strcpy(sym->str,str);
}
void set_IC(symbol *sym,int IC)
{
    sym->IC = IC;
}
void set_DC(symbol *sym,int DC)
{
    sym->DC = DC;
}

symbol* add_symbol(symbol **head, char *label, unsigned int pos)
{
    symbol *new = create_symbol();
    set_symbol(new,label,pos);
    new->next = NULL;
    if (*head == NULL)
    {
        *head = new;
        return new;
    }
    symbol *curr = *head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new;
        return new;
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
int get_symbol(symbol *node,char* name)
{
    symbol *curr = node;
    while (curr != NULL)
    {
        if (strcmp(curr->label,name)==0)
            return curr->label_pos;
        curr = curr->next;
    }
    return -1;
}
void print_num_arr(symbol *curr)
{
    int i;
    for (i = 0; i < 3; ++i) {
        printf("%d ",curr->nums[i]);
    }
    putchar('\n');
    int j;
    for (j = 0; j < 3; ++j) {
        if (curr->nums[j] > 0) decimalToBinary(curr->nums[j],12);
        else decimalToBinary(two_complement(curr->nums[j]),12);
        putchar('\n');
    }
    putchar('\n');
}
void free_symbol(symbol *head) {
    symbol* curr = head;
    while (curr != NULL) {
        symbol* temp = curr;
        curr = curr->next;
        free(temp);
    }
}