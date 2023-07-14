#include "includes.h"

char *str_allocate_cat(char *first_str, char* second_str) {
    char *str = (char *)malloc(strlen(first_str) + strlen(second_str) + 1);
    strcpy(str, first_str);
    strcat(str, second_str);
    return str;
}
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
int modifyASCII(int num)
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