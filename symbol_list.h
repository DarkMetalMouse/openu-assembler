#ifndef _SYMBOL_LIST_H
#define _SYMBOL_LIST_H

#include <stdint.h>

typedef enum symbol_type
{
    UNKNOWN,
    CODE,
    DATA
} symbol_type;

typedef enum symbol_attribute
{
    NONE,
    ENTRY,
    EXTERNAL
} symbol_attribute;

typedef union address
{
    uint16_t value;
    struct format
    {
        uint8_t offset : 4;
        uint8_t base : 4;
    } format;
} address;

typedef struct symbol symbol;
symbol *s_create(char *name, uint16_t address, symbol_type type, symbol_attribute attribute);
int s_set_name(symbol *s, char *name);
void s_set_type(symbol *s, symbol_type type);
void s_destroy(symbol *s);

typedef struct symbol_list symbol_list;
symbol_list *sl_create();
void sl_append(symbol_list *sl, symbol *s);
symbol *sl_get(symbol_list *sl, char *name);
void sl_destroy(symbol_list *sl);

#endif