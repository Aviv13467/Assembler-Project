#include "LinkedList.h"


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

node *get_node(node *head, int pos) {
    node *curr = head;
    while (curr != NULL) {
        if (curr->pos == pos)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

node* add_node(node **head, int pos, unsigned int code) {
    node *new = create_list();
    if (new == NULL)
        return NULL; // Handle allocation failure
    set_node(new, pos, code);
    new->next = NULL;
    if (*head == NULL) {
        *head = new;
        return new;
    }
    node *curr = *head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new;
    return new;
}


void print_node(node *head)
{
    node *curr = head;
    while (curr != NULL) {
        printf("%d\t%d\t%s\n", curr->pos,curr->code,curr->label);
        curr = curr->next;
    }
}

void delete_node(node **head, node *removed)
{
    if (*head == NULL || removed == NULL) return;
    if (*head == removed){
        *head = removed->next;
        free(removed);
        return;
    }
    node* curr = *head;
    while (curr->next != removed)
        curr = curr->next;
    curr->next = curr->next->next;
    if (curr->next == NULL) {
        return;
    }
    curr->next = removed->next;
    free(removed);
}
void set_label(node *curr,char *label)
{
    strcpy(curr->label,label);
}
void free_list(node *head)
{
    node* curr = head;
    while (curr != NULL) {
        node* temp = curr;
        curr = curr->next;
        free(temp);
    }
}