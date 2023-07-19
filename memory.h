#ifndef MEMORY_H
#define MEMORY_H

/*** HEADER FILES  ***/
#include "includes.h"
#include "symbol_table.h"
#include "utils.h"
/*** HEADER FILES  ***/

/*
 * These functions are responsible to shift each of the code to the corresponding location
 * opcode to bits 5-8
 * origin operand to bits 9-11
 * destination operand to bits 2-4
 * A,R,E to bits 0-1
 * the encode_combine is used to combine them all into a single 12-bit machine code.
 */
unsigned int encode_opcode(unsigned int opcode);
unsigned int encode_origin_operand(unsigned int origin_operand);
unsigned int encode_des_operand(unsigned int des_operand);
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand);

/*
 * These functions are responsible for the conversion of the machine code into Base64
 * encodeFirst takes the 6 left-most bits and separates them
 * encodeSecond takes the 6 right-most bits and separates them
 * returnEncode returns a char array in which the first element is the encodeFirst operation result, and the second element is the encodeSecond operation result
 * encodeBase64 function uses all of the above mention function to do it all in a single call and a return a newly created char array with the corresponding Base64 values
 */

char encodeFirst(unsigned int code);
char encodeSecond(unsigned int code);
char* returnEncode(char first, char second);
void encodeBase64(unsigned int code);
void file_encodeBase64(unsigned int code,FILE *ofp);

/*
 * These functions are responsible for the type of encoding
 * encode_immediate is used for encoding immediate values, e.g. 102,23,43 etc...
 * encode_combine_direct is used for encoding direct values, e.g. labels etc...
 */
unsigned int encode_immediate(unsigned int value);
unsigned int encode_combine_direct(unsigned int code,ARE type);
unsigned int encode_combine_label(unsigned int code);
unsigned int encode_combine_extern();

/*
 * Encoding of registers
 * encode_origin_reg_direct encodes the origin register 2-6
 * encode_des_reg_direct encodes the destination register in bits 7-11
 * encode_combine_reg encodes both registers into a single word.
 */
unsigned int encode_origin_reg_direct(unsigned int num);
unsigned int encode_des_reg_direct(unsigned int num);
unsigned int encode_combine_reg(unsigned int r1, unsigned int r2);
unsigned int two_complement(signed int num);

#endif