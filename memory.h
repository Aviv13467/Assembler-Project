#include "includes.h"
#include "symbol_table.h"
unsigned int encode_opcode(unsigned int opcode);
unsigned int encode_origin_operand(unsigned int origin_operand);
unsigned int encode_des_operand(unsigned int des_operand);
unsigned int encode_combine(unsigned int opcode, unsigned int origin_operand,unsigned int des_operand,unsigned int ARE);
char encodeFirst(unsigned int code);
char encodeSecond(unsigned int code);
char* returnEncode(char first, char second);
void encodeBase64(unsigned int code);
unsigned int encode_combine_immediate(unsigned int value, unsigned int ARE);
unsigned int encode_combine_direct(symbol *head,char* label, unsigned int ARE);
int encode_direct(unsigned int num);
unsigned int two_complement(signed int num);