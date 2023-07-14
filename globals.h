#define IC_START 100
typedef enum opcode{
    mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop, ILLEGAL_OPCODE = -1
}opcode;

typedef enum ADDRESS{
    NONE = 0,
    IMMEDIATE = 1,
    DIRECT = 3,
    DIRECT_REGISTER = 5
}ADDRESS;

typedef enum ARE{
    ABSOLUTE,
    EXTERN,
    RELOCATABLE
}ARE;