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
entry_table *create_entry(void);
void set_entry(entry_table *sym,char *name,int pos);
entry_table* add_entry(entry_table **head, char *label,int pos);
void print_entry_table(entry_table *head);
void fprint_entry_table(entry_table *head,FILE *ofp);
int get_entry(entry_table *node,char* name);
int isEmpty_entry(entry_table *head);
void free_entry(entry_table *head);

#endif
