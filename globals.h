#define IC_START 100
#ifndef GLOBALS_H
#define GLOBALS_H
typedef enum opcode{
    mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop, ILLEGAL_OPCODE = -1
}opcode;

typedef enum REGISTER{
    r0,r1,r2,r3,r4,r5,r6,r7
}REGISTER;

typedef enum ADDRESS{
    NONE = 0,
    IMMEDIATE = 1,
    DIRECT = 3,
    DIRECT_REGISTER = 5
}ADDRESS;

typedef enum ARE{
    ABSOLUTE,
    EXTERNAL,
    RELOCATABLE
}ARE;

typedef enum TYPE{
    data,string,entry,ext,ic
}TYPE;
#endif