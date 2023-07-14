#include "memory.h"
#include "utils.h"

/*
 * This function shifts the bits of the opcode to slots 5-8
 */
unsigned int encode_opcode(unsigned int opcode)
{
    unsigned int mask = opcode << 5;
    return mask;
}
/*
 * This function shifts the bits of the origin operand code to slots 9-11
 */
unsigned int encode_origin_operand(unsigned int origin_operand)
{
    unsigned int mask = origin_operand << 9;
    return mask;
}
/*
 * This function shifts the bits of the destination operand code to slots 2-4
 */
unsigned int encode_des_operand(unsigned int des_operand)
{
    unsigned int mask = des_operand << 2;
    return mask;
}
/*
 * This function combines all the code into one 12-bit word using all o
 */
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand,unsigned int ARE)
{
    unsigned int combine;
    combine = opcode | origin_operand | des_operand | ARE;
    return combine;
}
/*
void encodeBase64(unsigned int code)
{
    unsigned int base64a,base64b;
    base64a = code >> 6;
    base64b = code << 6;
    unsigned int mask64 = 4032;
    base64b &= mask64;
    base64b >>= 6;
    printf("%d\n",base64b);
    printf("The encoded Base64 is: %c%c", modifyASCII(base64a), modifyASCII(base64b));
}
 */
char encodeFirst(unsigned int code)
{
    unsigned int first;
    first = modifyASCII(code>>6);
    return first;
}
char encodeSecond(unsigned int code)
{
    unsigned int second, mask;
    second = code << 6;
    mask = 4032;
    second &= mask;
    second >>= 6;
    second = modifyASCII(second);
    return second;
}
char* returnEncode(char first, char second)
{
    char *ptr;
    ptr = (char*)malloc(sizeof(char)*3);
    ptr[0] = first;
    ptr[1] = second;
    ptr[3] = '\0';
    return ptr;
}
void encodeBase64(unsigned int code)
{
    char a,b;
    char *c;
    a = encodeFirst(code);
    b = encodeSecond(code);
    c = returnEncode(a,b);
    printf("%s",c);
    free(c);
}