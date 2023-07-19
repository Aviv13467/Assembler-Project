#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "includes.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int pos;
    unsigned int code;
    char label[MAX_LEN];
    struct node *next;
} node;

node *create_list(void);
void set_node(node *sym, int pos, unsigned int code);
node *get_node(node *head, int pos);
node *return_label(node* head);
node *add_node(node **head, int pos, unsigned int code);
void delete_node(node **head, node *removed);
void set_label(node *curr,char *label);
void print_node(node *head);
int get_IC(node *head);
void fprint_node(node *head,FILE *ofp);
void free_list(node *head);

#endif
