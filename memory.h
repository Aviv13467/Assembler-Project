#ifndef MEMORY_H
#define MEMORY_H

/*** HEADER FILES  ***/
#include <stdio.h>
#include <ctype.h>
#include "symbol_table.h"
#include "utils.h"
#include "globals.h"
/*** HEADER FILES  ***/

/*
 * encode_opcode function move the opcode bits to bits 5-8
 */
unsigned int encode_opcode(unsigned int opcode);
/*
 * encode_origin_operand function move the origin_operand bits to bits 9-11
 */
unsigned int encode_origin_operand(unsigned int origin_operand);
/*
 * encode_des_operand function moves destination_operand bits to 2-4
 */
unsigned int encode_des_operand(unsigned int des_operand);
/*
 * encode_combine function encodes all the previous encoding into one single 12-bit machine code
 */
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand);

/*
 * encodeFirst function separates the 6 leftmost bits and converts them into a single character
 */
char encodeFirst(unsigned int code);
/*
 * encodeSecond function separates the 6 rightmost bits and converts them into a single character
 */
char encodeSecond(unsigned int code);
/*
 * returnEncodes returns char pointer whereas the first element is the result of encodeFirst function and the second element is the result of encodeSecond resulting in a 2-character long string
 */
char* returnEncode(char first, char second);
/*
 * file_encodeBase64 writes to the given file the encoded machine code in Base64 format
 */
void file_encodeBase64(unsigned int code,FILE *ofp);

/*
 * These functions are responsible for the type of encoding
 * encode_immediate is used for encoding immediate values, e.g. 102,23,43 etc...
 * encode_combine_direct is used for encoding direct values, e.g. labels etc...
 */

/*
 * encode_absolute function encodes the machine code with an ABSOLUTE encoding to the A,R,E bits
 */
unsigned int encode_absolute(unsigned int value);
/*
 * encode_relocatable function encodes the machine code with a relocatable encoding to the A,R,E bits
 */
unsigned int encode_relocatable(unsigned int code);
/*
 * encode_extern function encodes the machine code with an extern encoding to the A,R,E bits
 */
unsigned int encode_extern(void);

/*
 * Encoding of registers
 * encode_origin_reg_direct encodes the origin register 2-6
 * encode_des_reg_direct encodes the destination register in bits 7-11
 * encode_combine_reg encodes both registers into a single word.
 */

/*
 * encode_origin_reg_direct function encodes the origin register in bits 2-6
 */
unsigned int encode_origin_reg_direct(unsigned int num);
/*
 * encode_des_reg_direct function encodes the destination register in bits 7-11
 */
unsigned int encode_des_reg_direct(unsigned int num);
/*
 * encode_combine_reg function encodes both registers into a single machine word
 */
unsigned int encode_combine_reg(unsigned int r1, unsigned int r2);
/*
 * two_complements takes a negative integer and converts it into a positive integer using the two_complements method
 */
unsigned int two_complement(signed int num);

#endif

