#ifndef _INSTRUCTION_LIST_H
#define _INSTRUCTION_LIST_H

#include "instruction.h"

typedef struct instruction_list instruction_list;

instruction_list *il_create();
void il_append(instruction_list *il, instruction *inst);
uint32_t il_read_next_word(instruction_list *il);

#endif