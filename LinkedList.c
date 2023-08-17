#include "LinkedList.h"
#include "memory.h"

node *create_list(void) {
    node *new = (node*)malloc(sizeof(node));
    if (new == NULL)
        exit(1);
    return new;
}

void set_node(node *sym, int pos, unsigned int code) {
    sym->pos = pos;
    sym->code = code;
}

node* add_node(node **head, int pos, unsigned int code) {
    node *new = create_list();
    node *curr;
    if (new == NULL)
        return NULL;
    set_node(new, pos, code);
    new->next = NULL;
    if (*head == NULL) {
        *head = new;
        return new;
    }
    curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new;
    return new;
}

void fprint_node(node *head,FILE *ofp)
{
    node *curr = head;
    while (curr != NULL) {
        file_encodeBase64(curr->code,ofp);
        curr = curr->next;
    }
}

void delete_node(node **head, node *removed)
{
    node *curr;
    if (*head == NULL || removed == NULL) return;
    if (*head == removed){
        *head = removed->next;
        free(removed);
        return;
    }
    curr = *head;
    while (curr->next != removed)
        curr = curr->next;
    curr->next = curr->next->next;
    if (curr->next == NULL) {
        return;
    }
    curr->next = removed->next;
    free(removed);
}
int get_IC(node *head)
{
    int count = 1;
    node *curr = head;
    if (curr == NULL) return -1;
    while (curr->next!=NULL)
    {
        count++;
        curr = curr->next;

    }
    return count;
}
void set_label(node *curr,char *label)
{
    strcpy(curr->label,label);
}
void free_list(node *head)
{
    node *curr, *temp;
    if (head == NULL) return;
    curr = head;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}
