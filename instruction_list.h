#ifndef _INSTRUCTION_LIST_H
#define _INSTRUCTION_LIST_H

#include "instruction_pass2.h"

typedef struct instruction_list_pass2 instruction_list_pass2;

instruction_list_pass2 *il_create();
void il_append(instruction_list_pass2 *il, instruction_pass2 *inst);
uint32_t il_read_next_word(instruction_list_pass2 *il);
uint16_t il_get_ic(instruction_list_pass2 *il);

#endif