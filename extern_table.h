#ifndef EXTERN_TABLE_H
#define EXTERN_TABLE_H

/*** HEADER FILES  ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
/*** HEADER FILES  ***/

typedef struct extern_table{
    char label[MAX_LABEL];
    int label_pos;
    struct extern_table *next;
}extern_table;

/*
 * create_extern function creates a new extern table using LinkedList.
 */
extern_table *create_extern(void);
/*
 * set_extern function set values to the given node in the table.
 */
void set_extern(extern_table *ext,char *name,int pos);
/*
 * add_extern function adds a new node to the extern table.
 */
extern_table* add_extern(extern_table **head, char *label,int pos);
/*
 * get_extern function is used to determine if a certain label is in the table
 */
int get_extern(extern_table *head,char *label);

/*
 * fprint_extern_table function prints the extern labels into the given file.
 */
void fprint_extern_table(extern_table *head,FILE *ofp);
/*
 * isEmpty_ext function checks whether the extern table is empty.
 */
int isEmpty_ext(extern_table *head);
/*
 * free_extern function deletes the entire table and frees the allocated memory.
 */
void free_extern(extern_table *head);

#endif
