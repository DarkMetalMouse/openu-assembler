/**
 * @file operand.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * API for creating all types of operands which are stored in a union
 */

#ifndef _OPERAND_H
#define _OPERAND_H

#include <stdint.h>
#include "error_handler.h"

#define MAX_OPERAND_COUNT 2

typedef enum operand_type
{
    immidiate,
    direct,
    indexed,
    reg
} operand_type;

typedef union address
{

    char *pass1;
    struct pass2
    {
        uint16_t value;
        unsigned int is_external : 1;
    } pass2;
} address;

typedef struct operand
{
    union data_type
    {
        uint16_t imm;

        address address;

        struct indexed
        {
            address address;
            unsigned int reg : 4;
        } indexed;

        unsigned int reg : 4;
    } data_type;
    operand_type type;
} operand;

/**
 * @brief create an immidiate type operand
 *
 * @param value the imm number
 * @return operand the operand
 */
operand o_create_immidiate(int16_t value);

/**
 * @brief create a register type operand
 *
 * @param reg the register number
 * @return operand the operand
 */
operand o_create_reg(unsigned int reg);

/**
 * @brief get the memory footprint of an operand
 *
 * @param operand the operand
 * @return int the footprint in words
 */
int get_operand_size(operand operand);

/**
 * @brief parse an operand from a string
 *
 * @param s
 * @param eh
 * @return operand
 */
operand parse_operand(char *s, error_handler *eh);

#endif