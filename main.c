#include "includes.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    preproces_file(argv[1]);
    /* first_pass(argv[1]); */
    /* decimalToBinary(5,6); */


    unsigned int opcode = 0, origin_operand = 5, des_operand = 3;
    unsigned int mask1 = opcode << 5, mask2 = origin_operand << 9, mask3 = des_operand << 2;
    /*
    printf("mask1:");
    decimalToBinary(mask1,12);
    putchar('\n');
    printf("mask2:");
    decimalToBinary(mask2,12);
    putchar('\n');
    printf("mask3:");
    decimalToBinary(mask3,12);
    putchar('\n');
     */
    unsigned int combine = mask1 | mask2 | mask3;
    printf("combine code is: ");
    decimalToBinary(combine,12);
    putchar('\n');

    /*
    printf("the decimal value of the combined code is: %d\n",combine);
    putchar('\n');
    unsigned int base64 = combine >> 5;
    printf("base64 is: %d\n",base64);
     */

    unsigned int base64a,base64b;
    base64a = combine >> 6;
    base64b = combine << 6;
    unsigned int mask64 = 4032;
    base64b &= mask64;
    base64b >>= 6;
    printf("%d\n",base64b);
    printf("The encoded Base64 is: %c%c", modifyASCII(base64a), modifyASCII(base64b));
    return 0;


}