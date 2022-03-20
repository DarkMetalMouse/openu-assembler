/**
 * @file instruction_pass2.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * 2nd pass instruction, used unions and bit-fields to process the different types of instruction words
 */

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

/**
 * @brief create a new instruction
 *
 * @param opcode the opcode
 * @param operand_count the number of operands
 * @param operands the array of operands
 * @param eh the error handler
 * @return instruction_pass2* a new instruction
 */
instruction_pass2 *i_create(opcode opcode, int operand_count, operand operands[], error_handler *eh);

/**
 * @brief get the number of words in the instruction
 *
 * @param inst the instruction
 * @return int the number of words
 */
int i_get_size(instruction_pass2 *inst);

/**
 * @brief get a word of the instruction
 * 
 * @param inst the instruction
 * @param i the word index
 * @return uint32_t the formatted 20bit word
 */
uint32_t i_get_word(instruction_pass2 *inst, int i);

/**
 * @brief print an instruction to the screen
 * this is used for debugging
 * @param inst the instruction
 */
void i_print(instruction_pass2 *inst);

#endif