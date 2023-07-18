#ifndef NEW_ENTRY_TABLE_H
#define NEW_ENTRY_TABLE_H
#include "globals.h"
#include "includes.h"
#include "utils.h"
#include "memory.h"

typedef struct entry_table{
    char label[31];
    int label_pos;
    struct entry_table *next;
}entry_table;
entry_table *create_entry(void);
void set_entry(entry_table *sym,char *name,int pos);
entry_table* add_entry(entry_table **head, char *label,int pos);
void print_entry_table(entry_table *head);
int get_entry(entry_table *node,char* name);
void free_entry(entry_table *head);

#endif //NEW_ENTRY_TABLE_H
