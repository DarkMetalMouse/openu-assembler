#ifndef _OPCODE_H
#define _OPCODE_H

typedef enum opcode
{
    mov,
    cmp,
    add,
    sub,

    lea,
    clr,
    not,
    inc,

    dec,
    jmp,
    bne,
    jsr,

    red,
    prn,
    rts,
    stop
} opcode;

int get_opcode_value(opcode opcode);
int get_opcode_funct(opcode opcode);
opcode get_opcode(char *name);

#endif