#include "memory.h"

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
 * This function combines all the codes into one 12-bit word with immediate address
 */
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand)
{
    opcode = encode_opcode(opcode);
    origin_operand = encode_origin_operand(origin_operand);
    des_operand = encode_des_operand(des_operand);
    unsigned int ARE = 0; /* In Instructions code, ARE bits are always ABSOLUTE */
    unsigned int combine;
    combine = opcode | origin_operand | des_operand | ARE;
    return combine;
}

/*
 * This functions combines value of immediate action (for ex. mov 23,...) and A,R,E bits into a machine code.
 */
unsigned int encode_immediate(unsigned int value)
{
    int ARE = 0;
    value = value<<2;
    return value|ARE;
}

/*
 * Used to encode label address code, 10 left-most bits are the address, the 2 rightmost are A,R,E (which is 1/2 depends on if EXTERN/RELOCATABLE)
 */
unsigned int encode_combine_direct(unsigned int code,ARE type)
{
    unsigned int combine = code|type;
    return combine;
}
unsigned int encode_combine_label(unsigned int code)
{
    unsigned int ARE = RELOCATABLE;
    unsigned int combine = code<<2;
    return combine|ARE;
}

/*
 * Encodes the first 6 digit to the left to the modified ASCII to be later used to convert ot Base64
 */
char encodeFirst(unsigned int code)
{
    int first;
    first = modifyASCII(code>>6);
    return first;
}
/*
 * Encodes the first 6 digit to the right to the modified ASCII to be later used to convert ot Base64
 */
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
/*
 * Returns a string of the values first,second from previous function to be converted to Base64
 */
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
/*
 * Shift the bits on the origin register code to bits 7-11
 */
unsigned int encode_origin_reg_direct(unsigned int num)
{
    return num<<7;
}
/*
 * Shift the bits on the origin register code to bits 2-6
 */
unsigned int encode_des_reg_direct(unsigned int num)
{
    return num<<2;
}
/*
 * Combines the origin and des register machine code if they share the same word.
 */
unsigned int encode_combine_reg(unsigned int r1, unsigned int r2)
{
    r1 = encode_origin_reg_direct(r1);
    r2 = encode_des_reg_direct(r2);
    return r1|r2;
}
/*
 * Two complements method to represent negative numbers in an unsigned integer.
 */
unsigned int two_complement(signed int num)
{
    return num&4095;
}