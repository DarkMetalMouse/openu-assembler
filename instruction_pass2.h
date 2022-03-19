#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>
#include "operand.h"

typedef struct instruction_pass2 instruction_pass2;

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

typedef enum ARE
{
    absolute = 1 << 2,
    relocatable = 1 << 1,
    external = 1 << 0
} ARE;

opcode get_opcode(char *name);

instruction_pass2 *i_create(opcode opcode, int operand_count, operand operands[]);
void i_set_next(instruction_pass2 *inst, instruction_pass2 *next);
instruction_pass2 *i_get_next(instruction_pass2 *inst);
int i_get_size(instruction_pass2 *inst);
uint32_t i_get_word(instruction_pass2 *inst, int i);

#endif