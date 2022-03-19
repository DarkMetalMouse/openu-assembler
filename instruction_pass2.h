#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>
#include "operand.h"
#include "opcode.h"
#include "error_handler.h"

typedef enum ARE
{
    absolute = 1 << 2,
    relocatable = 1 << 1,
    external = 1 << 0
} ARE;

typedef union word
{
    struct format
    {
        union data
        {
            struct __attribute__((__packed__)) funct_word
            {
                unsigned int dst_type : 2;
                unsigned int dst_reg : 4;
                unsigned int src_type : 2;
                unsigned int src_reg : 4;
                unsigned int funct : 4;
            } funct_word;
            uint16_t raw;

        } data;
        unsigned int ARE : 3;
        unsigned int _1 : 1;
    } format;
    unsigned int raw : 20;
} word;

typedef struct instruction_pass2
{
    word *words;
    int size;
    int filled;
} instruction_pass2;

int i2_size();
instruction_pass2 *i_create(opcode opcode, int operand_count, operand operands[], error_handler *eh);
void i_set_next(instruction_pass2 *inst, instruction_pass2 *next);
instruction_pass2 *i_get_next(instruction_pass2 *inst);
int i_get_size(instruction_pass2 *inst);
uint32_t i_get_word(instruction_pass2 *inst, int i);
void i_print(instruction_pass2 *inst);

#endif