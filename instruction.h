#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

typedef struct instruction instruction;

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

typedef enum operand_type
{
    immidiate,
    direct,
    indexed,
    reg
} operand_type;

typedef struct operand
{
    union data_type
    {
        uint16_t imm;

        struct address
        {
            uint16_t value;
            unsigned int is_external : 1;
        } address;

        struct indexed
        {
            struct address address;
            unsigned int reg : 4;
        } indexed;

        unsigned int reg : 4;
    } data_type;
    operand_type type;
} operand;

instruction *i_create(opcode opcode, int operand_count, operand operands[]);
void i_set_next(instruction *inst, instruction *next);
instruction *i_get_next(instruction *inst);
int i_get_size(instruction *inst);
uint32_t i_get_word(instruction *inst, int i);

#endif