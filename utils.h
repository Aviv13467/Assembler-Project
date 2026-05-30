#ifndef UTILS_H
#define UTILS_H

/*** HEADER FILES  ***/
#include "memory.h"
#include "LinkedList.h"
#include "extern_table.h"
#include "entry_table.h"
/*** HEADER FILES  ***/

/*
 * str_join function takes two char pointers and joins them together, it is being used for the extension addition of the assembly files
 * for example if the function is called with ("prog","as") the result will be a char pointer to "prog.as"
 */
char *str_join(char *first_str, char* second_str);

/*
 * number_of_operands function returns how many operands are expected for each command given, the range is 0-2
 */
int number_of_operands(opcode command);

/*
 * modifyASCII function takes the regular ascii values and converts them into the corresponding Base64 values in order to easily convert the final output from binary to Base64
 */
unsigned int modifyASCII(int num);

/*
 * remove_newline function removes the newline '\n' (if exists) at the end of a string
 */
char* remove_newline(char* str);

/*
 * opcode_string function returns the corresponding string for the opcode provided
 */
char* opcode_string(enum opcode index);

/*
 * register_string function returns the corresponding string for the register provided, for e.g. 4 will return "@r4"
 */
char* register_string(enum REGISTER reg);

/*
 * type_string function returns the corresponding string for the type provided, for e.g. 1 will return ".string"
 */
char* type_string(enum TYPE index);

/*
 * opcode_no function returns the corresponding opcode number for the opcode provided.
 */
int opcode_no(char* name);

/*
 * register_no function returns the corresponding register number for the register provided.
 */
int register_no(char* reg);

/*
 * command_valid function checks whether the command is valid
 */
int command_valid(char* opcode);

/*
 * isDigit function is used to determine whether a string contains a digit
 */
int isDigit(char *c);
/*
 * isRegister function is used to determine whether a register is valid
 */
int isRegister(char*str);

/*
 * isValid_macro function is used to determine whether a macro is valid
 */
int isValid_macro(char* name);

/*
 * isValid_label function is used to determine whether a label is valid
 */
int isValid_label(char *name);

/*
 * comma_check function is used to check if there are any consecutive commas present in the string
 */
int comma_check(char* str);
/*
 * redundant_comma_check function is used to check if there are any spare commas after a certain string.
 */
int redundant_comma_check(char* str);
/*
 * export_extern function is used to create and print to the .ext file
 */
void export_extern(char *ofp,extern_table *head);
/*
 * export_entry function is used to create and print to the .ent file
 */
void export_entry(char *ofp,entry_table *entry);
/*
 * write_counter function is used to create and write to the .ob file the IC,DC counter
 */
void write_counter(char *ofp, int IC,int DC);
/*
 * export_obj function is used to update and write to the .ob file the Base64 encoding
 */
int export_obj(char *ofp, node *head);
/*
 * remove_whitespaces functions removes trailing whitespaces from a given string
 */
void remove_whitespaces(char *str);
void removeLeadingWhitespaces(char *str);
#endif


