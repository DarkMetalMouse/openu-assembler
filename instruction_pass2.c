/**
 * @file instruction_pass2.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * 2nd pass instruction, it contains all the data formatted and ready to be printed to the file
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "instruction_pass2.h"
#include "operand.h"
#include "opcode.h"

instruction_pass2 *i_allocate(int size)
{
    instruction_pass2 *inst = malloc(sizeof(instruction_pass2));
    inst->size = size;
    inst->filled = 0;
    inst->words = malloc(sizeof(word) * size);
    return inst;
}

int i_get_size(instruction_pass2 *inst)
{
    return inst->size;
}

uint32_t i_get_word(instruction_pass2 *inst, int i)
{
    return inst->words[i].raw;
}

void i_fill(instruction_pass2 *inst, uint16_t data, ARE attribute)
{
    inst->words[inst->filled].format.ARE = attribute;
    inst->words[inst->filled++].format.data.raw = data;
}

void i_write_operand(instruction_pass2 *inst, operand operand, int is_dest)
{
    operand_type type = operand.type;
    ARE attribute;
    if (is_dest)
    {
        inst->words[1].format.data.funct_word.dst_type = type & 3; /* & 3 to make sure we only write 2 bits */
    }
    else
    {
        inst->words[1].format.data.funct_word.src_type = type & 3; /* & 3 to make sure we only write 2 bits */
    }

    switch (type)
    {
    case immidiate:
        i_fill(inst, operand.data_type.imm, absolute);

        break;
    case direct:
        attribute = operand.data_type.address.pass2.is_external ? external : relocatable;
        i_fill(inst, operand.data_type.address.pass2.value & 0xF0, attribute);
        i_fill(inst, operand.data_type.address.pass2.value & 0x0F, attribute);
        break;
    case indexed:
        attribute = operand.data_type.indexed.address.pass2.is_external ? external : relocatable;
        i_fill(inst, operand.data_type.indexed.address.pass2.value & 0xF0, attribute);
        i_fill(inst, operand.data_type.indexed.address.pass2.value & 0x0F, attribute);
        if (is_dest)
        {
            inst->words[1].format.data.funct_word.dst_reg = operand.data_type.indexed.reg;
        }
        else
        {
            inst->words[1].format.data.funct_word.src_reg = operand.data_type.indexed.reg;
        }
        break;
    case reg:
        if (is_dest)
        {
            inst->words[1].format.data.funct_word.dst_reg = operand.data_type.reg;
        }
        else
        {
            inst->words[1].format.data.funct_word.src_reg = operand.data_type.reg;
        }
        break;
    default:
        break;
    }
}

instruction_pass2 *i_create(opcode opcode, int operand_count, operand operands[], error_handler *eh)
{
    instruction_pass2 *inst = NULL;
    int size = 1; /* minimum instruction size */
    int i;

    size += operand_count ? 1 : 0; /* funct word space only applicable for instructions with operands*/
    for (i = 0; i < operand_count; i++)
    {
        size += get_operand_size(operands[i]);
    }
    inst = i_allocate(size);

    i_fill(inst, 1 << get_opcode_value(opcode), absolute);
    inst->filled++; /* skip funct for now */

    switch (operand_count)
    {
    case 2: /* handle source operand */

        i_write_operand(inst, operands[0], 0);

        /* fallthrough */
    case 1: /* handle destination operand */

        i_write_operand(inst, operands[operand_count - 1], 1); /* operand_count - 1 : 2 operands -> index 1; 1 operand -> index 0*/
        inst->words[1].format.data.funct_word.funct = get_opcode_funct(opcode);
        inst->words[1].format.ARE = absolute;

        /* fallthrough */
    default: /* case 0 */

        break;
    }
    return inst;
}

void i_print(instruction_pass2 *inst)
{
    int i;
    for (i = 0; i < inst->size; i++)
    {
        printf("%x\n", (uint32_t)inst->words[i].raw);
    }
    printf("---\n");
}
