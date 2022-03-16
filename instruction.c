#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "instruction.h"
#include "operand.h"

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

const int OPERAND_SIZE[] = {1, 2, 2, 0};

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
            uint16_t raw : 16;

        } data;
        unsigned int ARE : 3;
        unsigned int _1 : 1;
    } format;
    unsigned int raw : 20;
} word;

typedef struct instruction
{
    word *words;
    int size;
    int filled;
    instruction *next
} instruction;

int get_operand_size(operand operand)
{
    return OPERAND_SIZE[operand.type];
}

int within(int val, int min, int max)
{
    return min <= val && val <= max;
}

int is_n_operands(opcode opcode, int n)
{
    switch (n)
    {
    /* all n operand opcodes are within unique ranges */
    case 0:
        return within(OPCODE_VALUE[opcode], rts, stop);
    case 1:
        return within(OPCODE_VALUE[opcode], clr, prn);
    case 2:
        return within(OPCODE_VALUE[opcode], mov, lea);
    default:
        return 0;
    }
}

instruction *i_allocate(int size)
{
    instruction *inst = malloc(sizeof(instruction));
    inst->size = size;
    inst->filled = 0;
    inst->words = malloc(sizeof(word) * size);
    inst->next = NULL;
    return inst;
}

void i_set_next(instruction *inst, instruction *next)
{
    inst->next = next;
}

instruction *i_get_next(instruction *inst)
{
    return inst->next;
}

int i_get_size(instruction *inst)
{
    return inst->size;
}

uint32_t i_get_word(instruction *inst, int i)
{
    return inst->words[i].raw;
}

void i_fill(instruction *inst, uint16_t data, ARE attribute)
{
    inst->words[inst->filled].format.ARE = attribute;
    inst->words[inst->filled++].format.data.raw = data;
}

void i_write_operand(instruction *inst, operand operand, int is_dest)
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
        attribute = operand.data_type.address.is_external ? external : relocatable;
        i_fill(inst, operand.data_type.address.value & 0xF0, attribute);
        i_fill(inst, operand.data_type.address.value & 0x0F, attribute);
        break;
    case indexed:
        attribute = operand.data_type.indexed.address.is_external ? external : relocatable;
        i_fill(inst, operand.data_type.indexed.address.value & 0xF0, attribute);
        i_fill(inst, operand.data_type.indexed.address.value & 0x0F, attribute);
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

instruction *i_create(opcode opcode, int operand_count, operand operands[])
{
    instruction *inst = NULL;
    int size = 1; /* minimum instruction size */
    int i;
    if (!is_n_operands(opcode, operand_count))
    {
        /* ERROR OPERAND COUNT MISMATCH */
        return inst;
    }

    size += operand_count ? 1 : 0; /* funct word space only applicable for instructions with operands*/
    for (i = 0; i < operand_count; i++)
    {
        size += get_operand_size(operands[i]);
    }
    inst = i_allocate(size);

    i_fill(inst, 1 << OPCODE_VALUE[opcode], absolute);
    inst->filled++; /* skip funct for now */

    switch (operand_count)
    {
    case 2: /* handle source operand */

        i_write_operand(inst, operands[0], 0);

        /* fallthrough */
    case 1: /* handle destination operand */

        i_write_operand(inst, operands[operand_count - 1], 1); /* operand_count - 1 : 2 operands -> index 1; 1 operand -> index 0*/
        inst->words[1].format.data.funct_word.funct = OPCODE_FUNCT[opcode];
        inst->words[1].format.ARE = absolute;

        /* fallthrough */
    default: /* case 0 */

        break;
    }
    return inst;
}

void i_print(instruction *inst)
{
    int i;
    for (i = 0; i < inst->size; i++)
    {
        printf("%x\n", (uint32_t)inst->words[i].raw);
    }
    printf("---\n");
}

int main(int argc, char const *argv[])
{
    instruction *i;

    i = i_create(add, 2, (operand[]){o_create_reg(3), o_create_direct(146, 0)});
    i_print(i);

    i = i_create(prn, 1, (operand[]){o_create_immidiate(48)});
    i_print(i);

    i = i_create(lea, 2, (operand[]){o_create_direct(141, 0), o_create_reg(6)});
    i_print(i);

    i = i_create(inc, 1, (operand[]){o_create_reg(6)});
    i_print(i);

    i = i_create(mov, 2, (operand[]){o_create_reg(3), o_create_direct(0, 1)});
    i_print(i);

    i = i_create(sub, 2, (operand[]){o_create_reg(1), o_create_reg(4)});
    i_print(i);

    i = i_create(bne, 1, (operand[]){o_create_direct(140, 0)});
    i_print(i);

    i = i_create(cmp, 2, (operand[]){o_create_direct(0, 1), o_create_immidiate(-6)});
    i_print(i);

    i = i_create(bne, 1, (operand[]){o_create_index(149, 15, 0)});
    i_print(i);

    i = i_create(dec, 1, (operand[]){o_create_direct(149, 0)});
    i_print(i);

    i = i_create(sub, 2, (operand[]){o_create_index(104, 10, 0), o_create_reg(14)});
    i_print(i);

    i = i_create(stop, 0, (operand[]){});
    i_print(i);

    return 0;
}
