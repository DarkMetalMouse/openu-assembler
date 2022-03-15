#include "operand.h"

operand o_create_immidiate(int16_t value) {
    return (operand){.data_type.imm = value, .type = immidiate};
}

operand o_create_index(uint16_t address, unsigned int r, int is_external) {
    return 
            (operand){.data_type.index.address.is_external = is_external, //
            .data_type.index.address.value = address,                     //
            .data_type.index.reg = r,                                   //
            .type = index};
}

operand o_create_direct(uint16_t address, int is_external) {
        return 
            (operand){.data_type.address.is_external = is_external, //
            .data_type.address.value = address,                     //
            .type = direct};
}
operand o_create_reg(unsigned int r) {
    return (operand){.data_type.reg = r, .type = reg};
}
