#ifndef ENTRY_TABLE_H
#define ENTRY_TABLE_H

/*** HEADER FILES  ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*** HEADER FILES  ***/

typedef struct entry_table{
    char label[31];
    int label_pos;
    struct entry_table *next;
}entry_table;

/*
 * create_entry functions creates a new entry table based on a LinkedList.
 */
entry_table *create_entry(void);
/*
 * set_entry function sets values to the given node.
 */
void set_entry(entry_table *sym,char *name,int pos);
/*
 * add_entry function adds a new node to the entry table.
 */
entry_table* add_entry(entry_table **head, char *label,int pos);
/*
 * get_entry function is used to determine whether a label exist within the table.
 */
int get_entry(entry_table *head,char *label);

/*
 * fprint_entry_table function writes all the entries to the given file.
 */
void fprint_entry_table(entry_table *head,FILE *ofp);
/*
 * isEmpty_entry function checks whether the table is empty.
 */
int isEmpty_entry(entry_table *head);
/*
 * free_entry function deletes all nodes in the table and frees the allocated memory.
 */
void free_entry(entry_table *head);

#endif
