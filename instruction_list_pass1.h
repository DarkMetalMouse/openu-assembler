#ifndef _INSTRUCTION_LIST_PASS1_H
#define _INSTRUCTION_LIST_PASS1_H

#include "instruction_pass2.h"
#include "operand.h"
#include <ctype.h>

typedef struct instruction_pass1
{
    opcode opcode;
    operand operands[2];
    int operand_count;
    struct instruction_pass1 *next;

} instruction_pass1;

instruction_pass1 *i1_create(opcode opcode, operand operands[], int operand_count);
instruction_pass1 *i1_get_next(instruction_pass1 *i1);

typedef struct instruction_list_pass1
{
    instruction_pass1 *head;
    instruction_pass1 *tail;
    uint16_t ic;
} instruction_list_pass1;

instruction_list_pass1 *il1_create();
uint16_t il1_get_ic(instruction_list_pass1 *il1);
void il1_append(instruction_list_pass1 *il1, instruction_pass1 *i1);
int il1_get_length(instruction_list_pass1 *il1);
instruction_pass1 *il1_get_head(instruction_list_pass1 *il1);

#endif
