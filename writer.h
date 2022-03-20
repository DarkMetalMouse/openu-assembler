/**
 * @file writer.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * API for writing the 3 output files
 * external list api which contains all references to externals in the code for the .ext file
 */

#ifndef _WRITER_H
#define _WRITER_H
#include "symbol_list.h"

typedef struct external_value
{
    char *name;
    uint16_t address;
    struct external_value *next;
} external_value;

/**
 * @brief create a new external
 *
 * @param name the name of the external
 * @param address the address of the external
 * @return external_value* a new external
 */
external_value *e_create(char *name, uint16_t address);

typedef struct external_list
{
    external_value *head;
    external_value *tail;
} external_list;

/**
 * @brief create a new external list
 *
 * @return external_list* a new external list
 */
external_list *el_create();

/**
 * @brief append external to external list
 *
 * @param el the external list
 * @param e the external
 */
void el_append(external_list *el, external_value *e);

/**
 * @brief write the .ent file
 * 
 * @param fname the name of the file
 * @param sl the symbol list
 */
void write_entries(char *fname, symbol_list *sl);

/**
 * @brief write the .ext file
 * 
 * @param fname the name of the file
 * @param el the external list
 */
void write_externs(char *fname, external_list *el);

/**
 * @brief write the .ob file
 * 
 * @param fname the name of the file
 * @param inst_list the 2nd pass instruction list
 * @param inst_count the number of instructions
 * @param dl the data list
 * @param icf the final instuction counter
 */
void write_objects(char *fname, instruction_pass2 **inst_list, int inst_count, data_list *dl, int icf);

#endif