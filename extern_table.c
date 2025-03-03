#include "extern_table.h"

extern_table *create_extern(void)
{
    extern_table *new;
    new = (extern_table*) malloc(sizeof(extern_table));
    if(new == NULL)
        exit(EXIT_FAILURE);
    else return new;
}
void set_extern(extern_table *ext,char *name,int pos)
{
    strcpy(ext->label,name);
    ext->label_pos = pos;
}
extern_table* add_extern(extern_table **head, char *label,int pos)
{
    extern_table *new = create_extern();
    if (new == NULL)
        return NULL;

    set_extern(new, label, pos);
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
    } else {
        extern_table *curr = *head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new;
    }

    return new;
}
int get_extern(extern_table *head,char *label)
{
    extern_table *curr;
    curr = head;
    if (curr == NULL) return -2;
    while (curr!=NULL)
    {
        if (strcmp(curr->label,label) == 0) return 0;
        curr = curr->next;
    }
    return -1;
}
void fprint_extern_table(extern_table *head,FILE *ofp)
{
    extern_table *curr = head;
    while (curr!= NULL)
    {
        fprintf(ofp,"%s\t%d\n", curr->label, curr->label_pos);
        curr = curr->next;
    }
}
int isEmpty_ext(extern_table *head)
{
    return head == NULL;
}
void free_extern(extern_table *head)
{
    extern_table* curr;
    if (head == NULL) return;
    curr = head;
    while (curr != NULL) {
        extern_table* temp = curr;
        curr = curr->next;
        free(temp);
    }
}
