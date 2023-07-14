#define IC_START 100
enum {
    mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop, ILLEGAL_OPCODE = -1
}opcode;

enum{
    NONE = 0,
    IMMEDIATE = 1,
    DIRECT = 3,
    DIRECT_REGISTER = 5
}ADDRESS_ORIGIN;

enum{
    ABSOLUTE,
    EXTERN,
    RELOCATABLE
}ARE;