#include "memory.h"
#include "utils.h"
#include <string.h>
unsigned int encode_opcode(unsigned int opcode)
{
    unsigned int mask = opcode << 5;
    return mask;
}
unsigned int encode_origin_operand(unsigned int origin_operand)
{
    unsigned int mask = origin_operand << 9;
    return mask;
}
unsigned int encode_des_operand(unsigned int des_operand)
{
    unsigned int mask = des_operand << 2;
    return mask;
}
unsigned int encode_combine(unsigned int opcode,origin_operand, des_operand)
{
    unsigned int mask = opcode;
}
char* encodeBase64(unsigned int code)
{
    char str[4];
    unsigned int base64a,base64b;
    base64a = code >> 6;
    base64b = code << 6;
    unsigned int mask64 = 4032;
    base64b &= mask64;
    base64b >>= 6;
    printf("%d\n",base64b);
    printf("The encoded Base64 is: %c%c", modifyASCII(base64a), modifyASCII(base64b));
}