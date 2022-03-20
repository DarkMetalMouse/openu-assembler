/**
 * @file opcode.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Helper fuctions for opcodes
 */
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

/**
 * @brief get the opcode numeric value
 *
 * @param opcode the opcode
 * @return int the value
 */
int get_opcode_value(opcode opcode);

/**
 * @brief get the opcode funct number
 *
 * @param opcode the opcode
 * @return int the funct
 */
int get_opcode_funct(opcode opcode);

/**
 * @brief Get the opcode enum using its name
 *
 * @param name the string representation of the opcode
 * @return opcode the opcode
 */
opcode get_opcode(char *name);

/**
 * @brief check if the given opcode as a given number of operands
 *
 * @param opcode the opcode
 * @param n the number of operands
 * @return int whether the given opcode as a given number of operands
 */
int is_n_operands(opcode opcode, int n);

#endif