/**
 * @file symbol_list.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Symbol table api
 */

#ifndef _SYMBOL_LIST_H
#define _SYMBOL_LIST_H

#include <stdint.h>
#include "error_handler.h"

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

typedef struct symbol
{
    char *name;
    uint16_t address;
    symbol_type type;
    symbol_attribute attribute;
    struct symbol *next;

} symbol;
/**
 * @brief create a new symbol
 *
 * @param name the name of the symbol
 * @param address the address of the symbbol definition
 * @param type the type of the symbol (CODE or DATA)
 * @param attribute the attribute of the symbol (EXTERN or ENTRY)
 * @param eh the error handler
 * @return symbol* a new symbol
 */
symbol *s_create(char *name, uint16_t address, symbol_type type, symbol_attribute attribute, error_handler *eh);

/**
 * @brief get the attribute of the symbol
 *
 * @param s the symbol
 * @return symbol_attribute the attribute of the symbol
 */
symbol_attribute s_get_attribute(symbol *s);

/**
 * @brief get the address of the symbol
 *
 * @param s the symbol
 * @return uint16_t the address
 */
uint16_t s_get_address(symbol *s);

/**
 * @brief get the name of the symbol
 *
 * @param s the symbol
 * @return char* the name
 */
char *s_get_name(symbol *s);

/**
 * @brief get the type of the symbol
 *
 * @param s the symbol
 * @param type the type
 */
void s_set_type(symbol *s, symbol_type type);

/**
 * @brief set the address of the symbol
 *
 * @param s the symbol
 * @param address the address
 */
void s_set_address(symbol *s, uint16_t address);

/**
 * @brief free the memory used by the symbol
 *
 * @param s the symbol to free
 */
void s_destroy(symbol *s);

/**
 * @brief get the next symbol marked as entry
 * this fuction is complementary to sl_get_entry
 *
 * @param s the symbol
 * @return symbol* the next entry symbol
 */
symbol *s_get_entry(symbol *s);

typedef struct symbol_list
{
    symbol *head;
    symbol *tail;
} symbol_list;

/**
 * @brief create a new symbol list
 *
 * @return symbol_list* a new symbol list
 */
symbol_list *sl_create();

/**
 * @brief append symbol to symbol list
 *
 * @param sl the symbol list
 * @param s the symbol
 * @param eh the error handler
 */
void sl_append(symbol_list *sl, symbol *s, error_handler *eh);

/**
 * @brief get the symbol of the corresponding name
 * If no such symbol exists NULL is returned
 *
 * @param sl the symbol list
 * @param name the name of the desired symbol
 * @return symbol* the symbol
 */
symbol *sl_get(symbol_list *sl, char *name);

/**
 * @brief update address of data symbols with ICF
 *
 * @param sl the symbol list
 * @param icf the final instruction counter
 */
void sl_update_data_address(symbol_list *sl, uint16_t icf);

/**
 * @brief get the first symbol marked as entry
 *
 * @param sl the symbol list
 * @return symbol* the entry
 */
symbol *sl_get_entry(symbol_list *sl);

/**
 * @brief free the memory used by symbol list
 *
 * @param sl the symbol list to free
 */
void sl_destroy(symbol_list *sl);
#endif