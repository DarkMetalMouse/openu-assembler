#include "instruction.h"

/* a helper class for creating operands */

operand o_create_immidiate(int16_t value);
operand o_create_index(uint16_t address, unsigned int reg, int is_external);
operand o_create_direct(uint16_t address, int is_external);
operand o_create_reg(unsigned int reg);
