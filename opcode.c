/**
 * @file opcode.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Helper fuctions for opcodes
 */

#include "opcode.h"
#include <string.h>
#include "util.h"

#define OPCODE_COUNT 16

const char *OPCODE_STRING[] =
    {
        "mov",
        "cmp",
        "add",
        "sub",

        "lea",
        "clr",
        "not",
        "inc",

        "dec",
        "jmp",
        "bne",
        "jsr",

        "red",
        "prn",
        "rts",
        "stop"};

const int OPCODE_VALUE[] =
    {
        0,
        1,
        2,
        2,

        4,
        5,
        5,
        5,

        5,
        9,
        9,
        9,

        12,
        13,
        14,
        15};

const int OPCODE_FUNCT[] =
    {
        0,
        0,
        10,
        11,

        0,
        10,
        11,
        12,

        13,
        10,
        11,
        12,

        0,
        0,
        0,
        0};

opcode get_opcode(char *name)
{
    int i;
    for (i = 0; i < OPCODE_COUNT; i++)
    {
        if (strcmp(name, OPCODE_STRING[i]) == 0)
        {
            return (opcode)i;
        }
    }
    return -1;
}

int get_opcode_value(opcode opcode)
{
    return OPCODE_VALUE[opcode];
}
int get_opcode_funct(opcode opcode)
{
    return OPCODE_FUNCT[opcode];
}

int is_n_operands(opcode opcode, int n)
{
    switch (n)
    {
    /* all n operand opcodes are WITHIN unique ranges */
    case 0:
        return WITHIN(get_opcode_value(opcode), rts, stop);
    case 1:
        return WITHIN(get_opcode_value(opcode), clr, prn);
    case 2:
        return WITHIN(get_opcode_value(opcode), mov, lea);
    default:
        return 0;
    }
}