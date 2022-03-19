#ifndef _OPERAND_H
#define _OPERAND_H

#include <stdint.h>
/* a helper class for creating operands */

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

operand o_create_immidiate(int16_t value);
operand o_create_reg(unsigned int reg);
int get_operand_size(operand operand);
operand parse_operand(char *s);

#endif