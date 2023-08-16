#ifndef GLOBALS_H
#define GLOBALS_H

/*** DEFINES  ***/
#define IC_START 100
#define MAX_LEN 80
/*** DEFINES  ***/


/* ENUM for opcode */
typedef enum opcode{
    mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,red,prn,jsr,rts,stop, ILLEGAL_OPCODE = -1
}opcode;

/* ENUM for REGISTERS  */
typedef enum REGISTER{
    r0,r1,r2,r3,r4,r5,r6,r7
}REGISTER;

/* ENUM for ADDRESSING TYPES */
typedef enum ADDRESS{
    NONE = 0,
    IMMEDIATE = 1,
    DIRECT = 3,
    DIRECT_REGISTER = 5
}ADDRESS;

/* ENUM for A,R,E bits */
typedef enum ARE{
    ABSOLUTE,
    EXTERNAL,
    RELOCATABLE
}ARE;

/* ENUM for TYPES */
typedef enum TYPE{
    data,string,entry,ext,ic
}TYPE;
#endif
