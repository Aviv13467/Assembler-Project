#include "includes.h"
#include "string.h"

char *str_allocate_cat(char *first_str, char* second_str) {
    char *str = (char *)malloc(strlen(first_str) + strlen(second_str) + 1);
    strcpy(str, first_str);
    strcat(str, second_str);
    return str;
}
/*
 * Flushes the strtok buffer.
 */
void flush_strtok(void)
{
    char *trash = NULL;
    trash = strtok(NULL," ");
}
/*
 * This functions converts a decimal number into it's binary representation, the user has a control over how many leading-zeros to add.
 * for example if the users inputs the decimal number 3 and 4 as leading zeros, the output will be: 0011;
 */
void decimalToBinary(unsigned int decimal,int zeros) {

    unsigned binary[12]; // Assuming 16-bit short integers
    int i = 0;

    while (decimal > 0) {
        binary[i] = decimal & 1; // Get the least significant bit
        decimal >>= 1; // Right-shift decimal by 1 bit
        i++;
    }
    // Print leading zeros if necessary
    int j;
    for (j = i; j < zeros; j++) {
        printf("0 ");
    }
    for (j= i - 1; j >= 0; j--) {
        printf("%d ", binary[j]);
    }
}
/*
 * This function modifies ASCII values, so it can return the corresponding values to translate to Base64
 */
unsigned int modifyASCII(int num)
{
    if (num >= 0 && num <= 25)
        return num+65;
    else if (num >=26 && num <= 51)
        return num+71;
    else if (num >= 52 && num<= 61)
        return num-4;
    else if (num == 62)
        return 43;
    else if (num == 63)
        return 47;
}
char* remove_newline(char* str)
{
    str[strlen(str)-1] = '\0';
    return str;
}
char* opcode_string(enum opcode index)
{
    char* str[] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
    return str[index];
}
int opcode_no(char* name)
{
    char *cpy = name;
    cpy = remove_newline(cpy);
    int i;
    for (i = 0; i < 15; ++i) {
        if (strcmp(cpy, opcode_string(i)) == 0)
            return i;
        else
            fprintf(stderr,"INVALID COMMAND\n");
    }
    return -1;
}
int doesExist_macro(char* name)
{
    int i;
    for (i = 0; i < 15 ; ++i)
    {
        if (strcmp(name,opcode_string(i)) == 0)
            return 1;
    }
    return 0;
}
void print_arr(char* arr)
{
    int i = 0;
    for (i = 0; i < strlen(arr); ++i) {
        if (arr[i] == 10) printf(" newline ");
        if (arr[i] == '\0') printf(" null ");
        if (arr[i] == '\xe2') printf(" \" ");
        else printf("%c ",arr[i]);
    }
    putchar('\n');
}

