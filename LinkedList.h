#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int pos;
    unsigned int code;
    struct node *next;
} node;

node *create_list(void);
void set_node(node *sym, int pos, unsigned int code);
node *get_node(node *head, int pos);
node *add_node(node **head, int pos, unsigned int code);
void print_node(node *head);
void free_list(node *head);

#endif // LINKEDLIST_H
