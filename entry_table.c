#include "entry_table.h"

entry_table *create_entry(void)
{
    entry_table *new;
    new = (entry_table*) malloc(sizeof(entry_table));
    if(new == NULL)
        exit(EXIT_FAILURE);
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
int get_entry(entry_table *head,char *label)
{
    entry_table *curr;
    curr = head;
    if (curr == NULL) return -2;
    while (curr!=NULL)
    {
        if (strcmp(curr->label,label) == 0) return 0;
        curr = curr->next;
    }
    return -1;
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
