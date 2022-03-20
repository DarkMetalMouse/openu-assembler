/**
 * @file instruction_list_pass1.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * 1st pass instruction list, it holds the opcode and arguments as symbol names if needed
 */
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
    int line;
    struct instruction_pass1 *next;

} instruction_pass1;

/**
 * @brief create a new instruction
 *
 * @param opcode the opcode
 * @param operands an araray of the operands
 * @param operand_count the length of operands
 * @param eh the error handler
 * @return instruction_pass1* a new instruction
 */
instruction_pass1 *i1_create(opcode opcode, operand operands[], int operand_count, error_handler *eh);

/**
 * @brief get the instruction after the given one in the list
 *
 * @param i1 the given instruction
 * @return instruction_pass1* the next instruction
 */
instruction_pass1 *i1_get_next(instruction_pass1 *i1);

typedef struct instruction_list_pass1
{
    instruction_pass1 *head;
    instruction_pass1 *tail;
    uint16_t ic;
} instruction_list_pass1;

/**
 * @brief create a new instruction list
 *
 * @return instruction_list_pass1* a new instruction list
 */
instruction_list_pass1 *il1_create();

/**
 * @brief get the instruction counter (total size of instructions)
 *
 * @param il1 the instruction list
 * @return uint16_t the IC
 */
uint16_t il1_get_ic(instruction_list_pass1 *il1);

/**
 * @brief append an instruction to the list
 *
 * @param il1 the instruction list
 * @param i1 the instruction to append
 */
void il1_append(instruction_list_pass1 *il1, instruction_pass1 *i1);

/**
 * @brief get the number of instructions in the list
 *
 * @param il1 the instruction list
 * @return int the number of instructions
 */
int il1_get_length(instruction_list_pass1 *il1);

/**
 * @brief get the first instructions
 *
 * @param il1 the instruction list
 * @return instruction_pass1* the first instruction
 */
instruction_pass1 *il1_get_head(instruction_list_pass1 *il1);

/**
 * @brief free the memory used by instruction list
 * 
 * @param il1 the instruction list
 */
void il1_destroy(instruction_list_pass1 *il1);

#endif
