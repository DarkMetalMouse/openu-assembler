/**
 * @file instruction_list_pass1.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Implementation of the 1st pass instruction list using a linked list
 */

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

instruction_pass1 *i1_create(opcode opcode, operand operands[2], int operand_count, error_handler *eh)
{
    instruction_pass1 *i1;
    if (!is_n_operands(opcode, operand_count))
    {
        error(eh, OPERAND_COUNT_MISMATCH, 0); /* keep going to avoid segfaults in the future */
    }
    switch (operand_count)
    {
    case 0:
        break;
    case 1:
        if (!is_legal_dst_operand(opcode, operands[0]))
        {
            error(eh, ILLEGAL_OPERAND_TYPE, 0);
        }
        break;
    case 2:
        if (!is_legal_dst_operand(opcode, operands[1]))
        {
            error(eh, ILLEGAL_OPERAND_TYPE, 0);
        }
        if (!is_legal_dst_operand(opcode, operands[0]))
        {
            error(eh, ILLEGAL_OPERAND_TYPE, 0);
        }
        break;
    default:

        break;
    }

    i1 = malloc(sizeof(instruction_pass1));
    i1->opcode = opcode;
    i1->operands[0] = operands[0];
    i1->operands[1] = operands[1];
    i1->operand_count = operand_count;
    i1->line = eh_get_line(eh);
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

void i1_destroy(instruction_pass1 *i1)
{
    free(i1);
}

void il1_destroy(instruction_list_pass1 *il1)
{
    instruction_pass1 *ptr = il1->head;
    while (ptr != NULL)
    {
        instruction_pass1 *tmp = ptr;
        ptr = ptr->next;
        i1_destroy(tmp);
    }
    free(il1);
}