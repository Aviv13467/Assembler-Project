#include "includes.h"
#include "symbol_table.h"
unsigned int encode_opcode(unsigned int opcode);
unsigned int encode_origin_operand(unsigned int origin_operand);
unsigned int encode_des_operand(unsigned int des_operand);
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand);
char encodeFirst(unsigned int code);
char encodeSecond(unsigned int code);
char* returnEncode(char first, char second);
void encodeBase64(unsigned int code);
unsigned int encode_immediate(unsigned int value);
unsigned int encode_combine_direct(unsigned int code,ARE type);
unsigned int encode_origin_reg_direct(unsigned int num);
unsigned int encode_des_reg_direct(unsigned int num);
unsigned int encode_combine_reg(unsigned int r1, unsigned int r2);
unsigned int two_complement(signed int num);