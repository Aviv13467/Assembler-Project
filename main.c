#include "includes.h"
#include "utils.h"
#include "memory.h"
#include "first_pass.h"
#include "globals.h"
#include "LinkedList.h"
int main(int argc, char *argv[]) {


    preproces_file(argv[1]);
    first_pass(argv[1]);

    /*
    unsigned int opcode = sub, origin_operand = DIRECT_REGISTER, des_operand = DIRECT_REGISTER;
    unsigned int mask1 = encode_opcode(opcode);
    unsigned int mask2 = encode_origin_operand(origin_operand);
    unsigned int mask3 = encode_des_operand(des_operand);

    unsigned code = encode_combine(mask1, mask2, mask3);
    unsigned int reg1 = 1;
    unsigned int reg4 = 4;
    unsigned int result1 = encode_origin_reg_direct(reg1);
    unsigned int result2 = encode_des_reg_direct(reg4);
    unsigned int result3 = encode_combine_reg(result1,result2);
    decimalToBinary(result3,12);
     */

    return 0;


}