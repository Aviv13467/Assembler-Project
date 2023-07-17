#include "parse_line.h"
#include "globals.h"
#include <string.h>
#include "utils.h"
int number_of_operands(opcode command)
{
    switch (command) {
        /*
         * opcode with 2 operands: mov,cmp,add,sub,lea
         */
        case mov: return 2;
        case cmp: return 2;
        case add: return 2;
        case sub: return 2;
        case lea: return 2;
         /*
         * opcode with 1 operand: not,clr,inc,dec,jmp,bne,red,prn,jsr
         */
        case not: return 1;
        case clr: return 1;
        case inc: return 1;
        case dec: return 1;
        case jmp: return 1;
        case bne: return 1;
        case red: return 1;
        case prn: return 1;
        case jsr: return 1;
        /*
        * opcode with no operands: rts,stop
        */
        case rts: return 0;
        case stop: return 0;

        /*
         * INVALID command
         */
        case ILLEGAL_OPCODE: return -1;
    }
}
int is_register(char* var)
{
    int i;
    for (i = 0; i < 8; ++i) {
        if(strcmp(var, register_string(i)) == 0) return 1;
    }
    return 0;
}