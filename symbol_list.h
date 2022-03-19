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

typedef struct symbol symbol;
symbol *s_create(char *name, uint16_t address, symbol_type type, symbol_attribute attribute);
int s_set_name(symbol *s, char *name);
int s_get_name_length(symbol *s);
symbol_attribute s_get_attribute(symbol *s);
uint16_t s_get_address(symbol *s);
char *s_get_name(symbol *s);
void s_set_type(symbol *s, symbol_type type);
void s_set_address(symbol *s, uint16_t address);
void s_destroy(symbol *s);
symbol *s_get_entry(symbol *s);

typedef struct symbol_list symbol_list;
symbol_list *sl_create();
void sl_append(symbol_list *sl, symbol *s);
symbol *sl_get(symbol_list *sl, char *name);
void sl_destroy(symbol_list *sl);
void sl_update_data_address(symbol_list *sl, uint16_t icf);
symbol *sl_get_entry(symbol_list *sl);
#endif