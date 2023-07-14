#include "includes.h"
#include "utils.h"
#include "memory.h"
#include "globals.h"
int main(int argc, char *argv[])
{
    preproces_file(argv[1]);
    /* first_pass(argv[1]); */
    /* decimalToBinary(5,6); */

    unsigned int opcode = sub, origin_operand = DIRECT_REGISTER, des_operand = DIRECT_REGISTER;
    /*
    unsigned int mask1 = opcode << 5, mask2 = origin_operand << 9, mask3 = des_operand << 2;
     */

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

    /*
    unsigned int combine = mask1 | mask2 | mask3;
    printf("combine code is: ");
    decimalToBinary(combine,12);
    putchar('\n');
     */

    /*
    printf("the decimal value of the combined code is: %d\n",combine);
    putchar('\n');
    unsigned int base64 = combine >> 5;
    printf("base64 is: %d\n",base64);
     */

    /*
    unsigned int base64a,base64b;
    base64a = combine >> 6;
    base64b = combine << 6;
    unsigned int mask64 = 4032;
    base64b &= mask64;
    base64b >>= 6;
    printf("%d\n",base64b);
    printf("The encoded Base64 is: %c%c", modifyASCII(base64a), modifyASCII(base64b));
     */


    unsigned int mask1 = encode_opcode(opcode);
    unsigned int mask2 = encode_origin_operand(origin_operand);
    unsigned int mask3 = encode_des_operand(des_operand);
    unsigned int mask4 = 0;
    /*
    encodeBase64(encode_combine(mask1,mask2,mask3));
     */
    unsigned code = encode_combine(mask1,mask2,mask3,mask4);

    /*
    char a,b;
    char *c;
    a = encodeFirst(code);
    b = encodeSecond(code);
    c = returnEncode(a,b);
    printf("%s",c);
    free(c);
    encodeBase64(code);
     */
    signed x = -5;
    unsigned mask = encode_direct(-5);
    unsigned int result = encode_combine_direct((mask&4095),ABSOLUTE);
    decimalToBinary(result,12);
    putchar('\n');
    encodeBase64(result);
    return 0;


}