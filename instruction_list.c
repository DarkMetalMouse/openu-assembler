#include <stdint.h>
#include <stdlib.h>

typedef enum opcode {
    mov= 1<<0,
    cmp=1<<1,
    add=1<<2,
    sub=1<<2,

    lea=1<<4,
    clr=1<<5,
    not=1<<5,
    inc=1<<5,

    dec=1<<5,
    jmp=1<<9,
    bne=1<<9,
    jsr=1<<9,

    red=1<<12,
    prn=1<<13,
    rts=1<<14,
    stop=1<<15
} opcode;

typedef enum funct {
    mov_funct=0,
    cmp_funct=0,
    add_funct=10,
    sub_funct=11,

    lea_funct=0,
    clr_funct=10,
    not_funct=11,
    inc_funct=12,

    dec_funct=13,
    jmp_funct=10,
    bne_funct=11,
    jsr_funct=12,

    red_funct=0,
    prn_funct=0,
    rts_funct=0,
    stop_funct=0
} funct;

typedef enum ARE {
    A=1<<2,
    R=1<<1,
    E=1<<0
} ARE;

typedef union line
{
    struct format
    {
        unsigned int data : 16;
        unsigned int ARE:3;
        unsigned int _1:1;
    } format;
    unsigned int raw : 20;
} line;


typedef struct instruction
{
    line *lines;
    int size;
} instruction;

typedef struct operand
{
    union data {
        uint16_t imm;
        uint16_t address;
        struct index
        {
            uint16_t address;
            unsigned int reg : 4;
        } index;
        unsigned int reg : 4;
    } data;
    unsigned int type : 2; 

} openrand;



instruction *i_create_no_operand(opcode opcode) {
    instruction *i = NULL;
    switch (opcode)
    {
    case rts:
    case stop:
        
        i = i_create_n(1);
        i->lines[0].format.data = opcode;
        break;
    default:
        /* ERROR NOT ENOUGH ARGUMENTS */
        break;
    }
    return i;
}

instruction *i_create_one_operand(opcode opcode) {
    instruction *i = NULL;
    switch (opcode)
    {
    case clr | not | inc | dec: /* They have the same value, it will be optimized*/
    case jmp | bne | jsr:
    case red:
    case prn:
    case stop:
        i = i_create_n(1);
        i->lines[0].format.data = opcode;
        break;
    default:
        /* ERROR NOT ENOUGH ARGUMENTS */
        break;
    }
    return i;
}

instruction *i_create_n(int size) {
    instruction *i = malloc(sizeof(instruction));
    i->size = size;
    i->lines = malloc(sizeof(line) * size);
    return i;
}

int main(int argc, char const *argv[])
{
    return 0;
}
