#ifndef EXTERN_TABLE_H
#define EXTERN_TABLE_H

#include "includes.h"

typedef struct extern_table{
    char label[31];
    int label_pos;
    struct extern_table *next;
}extern_table;

extern_table *create_extern(void);
void set_extern(extern_table *ext,char *name,int pos);
extern_table* add_extern(extern_table **head, char *label,int pos);
void print_extern_table(extern_table *head);
void fprint_extern_table(extern_table *head,FILE *ofp);
int get_extern(extern_table *node,char* name);
int isEmpty_ext(extern_table *head);
void free_extern(extern_table *head);

#endif
