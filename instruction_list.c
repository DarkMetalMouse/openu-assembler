#include "instruction_list.h"
#include "instruction.h"
#include <stdio.h>

typedef struct instruction_list
{
    instruction *head;
    instruction *tail;

    instruction *reading;
    int i;
} instruction_list;

instruction_list *il_create() {
    instruction_list *il = malloc(sizeof(instruction_list));
    il->head = NULL;
    il->tail = NULL;
}

void il_append(instruction_list *il, instruction *inst) {
    if(il->head == NULL) 
    {
        il->head = inst;
        il->tail = inst;
    }
    i_set_next(il->tail, inst);
    il->tail = inst;
}

uint32_t il_read_next_word(instruction_list *il) {
    if (il->reading == NULL)
    {
        if (il->i == 0)
        {
            il->reading = il->head;
        } else {
            return 0;
        }
    }
    if(i_get_size(il->reading) >= il->i) {
        il->reading = i_get_next(il->reading);
        if (il->reading) {
            il->i = 0;
        }
    }
    if (il->reading) {
        return i_get_word(il->reading, il->i++);
    }
}

/* void il_seek_start(instruction_list *il) {
    il->reading = NULL;
    il->i = 0;
} */
