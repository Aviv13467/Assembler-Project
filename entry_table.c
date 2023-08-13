#include "entry_table.h"

entry_table *create_entry(void)
{
    entry_table *new;
    new = (entry_table*) malloc(sizeof(entry_table));
    if(new == NULL)
        exit(1);
    else return new;
}
void set_entry(entry_table *sym,char *name,int pos)
{
    strcpy(sym->label,name);
    sym->label_pos = pos;
}

entry_table* add_entry(entry_table **head, char *label,int pos)
{
    entry_table *new = create_entry();
    if (new == NULL)
        return NULL;

    set_entry(new, label, pos);
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
    } else {
        entry_table *curr = *head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new;
    }

    return new;
}

void print_entry_table(entry_table *head)
{
    entry_table *curr = head;
    while (curr!= NULL)
    {
        printf("%s\t%d\n", curr->label, curr->label_pos);
        curr = curr->next;
    }
}
void fprint_entry_table(entry_table *head,FILE *ofp)
{
    entry_table *curr = head;
    while (curr!= NULL)
    {
        fprintf(ofp,"%s\t%d\n", curr->label, curr->label_pos);
        curr = curr->next;
    }
}

int get_entry(entry_table *node,char* name)
{
    entry_table *curr = node;
    while (curr != NULL)
    {
        if (strcmp(curr->label,name)==0)
            return curr->label_pos;
        curr = curr->next;
    }
    return -1;
}
int isEmpty_entry(entry_table *head)
{
    return head == NULL;
}
void free_entry(entry_table *head)
{
    entry_table* curr,*temp;
    if (head == NULL) return;
    curr = head;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        if (temp!=NULL) free(temp);
    }
}