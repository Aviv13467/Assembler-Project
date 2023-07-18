#include "parse_line.h"
#include "globals.h"
#include "utils.h"
int number_of_operands(opcode command)
{
    switch (command) {
        /*
         * opcode with 2 operands: mov,cmp,add,sub,lea
         */
        case mov:
        case cmp:
        case add:
        case sub:
        case lea:
            return 2;
         /*
         * opcode with 1 operand: not,clr,inc,dec,jmp,bne,red,prn,jsr
         */
        case not:
        case clr:
        case inc:
        case dec:
        case jmp:
        case bne:
        case red:
        case prn:
        case jsr:
            return 1;
        /*
        * opcode with no operands: rts,stop
        */
        case rts:
        case stop:
            return 0;

        /*
         * INVALID command
         */
        case ILLEGAL_OPCODE: return -1;
    }
}
