#ifndef UTILS_H
#define UTILS_H
#include "LinkedList.h"
#include "extern_table.h"
#include "entry_table.h"

char *str_allocate_cat(char *first_str, char* second_str);
void flush_strtok(void);
void decimalToBinary(unsigned int decimal,int zeros);
unsigned int modifyASCII(int num);
char* remove_newline(char* str);
char* opcode_string(enum opcode index);
char* register_string(enum REGISTER reg);
char* type_string(enum TYPE index);
int opcode_no(char* name);
int register_no(char* reg);
int command_valid(char* opcode);
int doesExist_macro(char* name);
int isDigit(char *c);
int isRegister(char*str);
void print_arr(char* arr);
int isValid_macro(char* name);
void b64(node *head);
void export_extern(char *ofp,extern_table *head);
void export_entry(char *ofp,entry_table *entry);
#endif