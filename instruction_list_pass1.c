#include <stdlib.h>
#include <ctype.h>
#include "operand.h"
#include "instruction_list_pass1.h"

#define CODE_OFFSET 100

instruction_list_pass1 *il1_create()
{
    instruction_list_pass1 *il1 = malloc(sizeof(instruction_list_pass1));
    il1->head = NULL;
    il1->tail = NULL;
    il1->ic = CODE_OFFSET;
    /*     il1->reading = NULL;
        il1->i = 0; */
    return il1;
}

uint16_t il1_get_ic(instruction_list_pass1 *il1)
{
    return il1->ic;
}

instruction_pass1 *i1_create(opcode opcode, operand operands[2], int operand_count)
{
    instruction_pass1 *i1 = malloc(sizeof(instruction_pass1));
    i1->opcode = opcode;
    i1->operands[0] = operands[0];
    i1->operands[1] = operands[1];
    i1->operand_count = operand_count;
    i1->next = NULL;
    return i1;
}

int i1_get_size(instruction_pass1 *i1)
{
    int i, size = 1; /* opcode size */

    if (i1->operand_count)
        size++; /* funct size */
    for (i = 0; i < i1->operand_count; i++)
    {
        size += get_operand_size(i1->operands[i]);
    }
    return size;
}

void il1_append(instruction_list_pass1 *il1, instruction_pass1 *i1)
{
    il1->ic += i1_get_size(i1);
    if (il1->head == NULL)
    {
        il1->head = i1;
        il1->tail = i1;
        return;
    };
    il1->tail->next = i1;
    il1->tail = i1;
}

int il1_get_length(instruction_list_pass1 *il1)
{
    int len = 0;
    instruction_pass1 *ptr = il1->head;
    while (ptr != NULL)
    {
        len++;
        ptr = ptr->next;
    }
    return len;
}

instruction_pass1 *il1_get_head(instruction_list_pass1 *il1)
{
    return il1->head;
}

instruction_pass1 *i1_get_next(instruction_pass1 *i1)
{
    return i1->next;
}
