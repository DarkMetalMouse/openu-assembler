#include "instruction_list.h"
#include "instruction_pass2.h"
#include <stdio.h>
#include <stdlib.h>

#define CODE_OFFSET 100

typedef struct instruction_list_pass2
{
    instruction_pass2 *head;
    instruction_pass2 *tail;

    uint16_t ic;

    instruction_pass2 *reading;
    int i;
} instruction_list_pass2;

instruction_list_pass2 *il_create()
{
    instruction_list_pass2 *il = malloc(sizeof(instruction_list_pass2));
    il->head = NULL;
    il->tail = NULL;
    il->ic = CODE_OFFSET;
    il->reading = NULL;
    il->i = 0;
    return il;
}

uint16_t il_get_ic(instruction_list_pass2 *il)
{
    return il->ic;
}

void il_append(instruction_list_pass2 *il, instruction_pass2 *inst)
{
    il->ic += i_get_size(inst);
    if (il->head == NULL)
    {
        il->head = inst;
        il->tail = inst;
        return;
    }
    i_set_next(il->tail, inst);
    il->tail = inst;
}

uint32_t il_read_next_word(instruction_list_pass2 *il)
{
    if (il->reading == NULL)
    {
        if (il->i == 0)
        {
            il->reading = il->head;
        }
        else
        {
            return 0;
        }
    }
    if (i_get_size(il->reading) >= il->i)
    {
        il->reading = i_get_next(il->reading);
        if (il->reading)
        {
            il->i = 0;
        }
    }
    if (il->reading)
    {
        return i_get_word(il->reading, il->i++);
    }
    return 0;
}

/* void il_seek_start(instruction_list *il) {
    il->reading = NULL;
    il->i = 0;
} */
