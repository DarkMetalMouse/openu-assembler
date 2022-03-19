#ifndef _WRITER_H
#define _WRITER_H
#include "symbol_list.h"

typedef struct external_value
{
    char *name;
    uint16_t address;
    struct external_value *next;
} external_value;

external_value *e_create(char *name, uint16_t address);


typedef struct external_list
{
    external_value *head;
    external_value *tail;
} external_list;

external_list *el_create();
void el_append(external_list *el, external_value *e);

void write_entries(char *fname, symbol_list *sl);
void write_externs(char *fname, external_list *el);
void write_objects(char *fname, instruction_pass2 **inst_list, int inst_count, data_list *dl, int icf);

#endif