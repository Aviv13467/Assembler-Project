#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*** HEADER FILES  ***/
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
/*** HEADER FILES  ***/

typedef struct node {
    int pos;
    unsigned int code;
    char label[MAX_LEN];
    struct node *next;
} node;

/*
 * create_list function creates a new LinkedList
 */
node *create_list(void);
/*
 * set_node function set values to the fields in the given node
 */
void set_node(node *sym, int pos, unsigned int code);
/*
 * add_node function adds a new node to the LinkedList
 */
node *add_node(node **head, int pos, unsigned int code);
/*
 * delete_node functions deletes a given node from the LinkedList
 */
void delete_node(node **head, node *removed);
/*
 * set_label functions sets the label field in the *curr node
 */
void set_label(node *curr,char *label);
/*
 * get_IC function returns the IC value of the given node
 */
int get_IC(node *head);
/*
 * fprint_node function prints all the nodes in the LinkedList to the given file
 */
void fprint_node(node *head,FILE *ofp);
/*
 * free_list function removes all nodes from the LinkedList and frees the allocated memory
 */
void free_list(node *head);

#endif
