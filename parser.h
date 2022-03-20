/**
 * @file parser.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * API for 1st pass and 2nd pass parsing
 */

#ifndef _PARSER_H
#define _PARSER_H
#include "symbol_list.h"
#include "instruction_list_pass1.h"
#include "data_list.h"
#include "instruction_pass2.h"
#include "writer.h"

/**
 * @brief parse a line from the file in the 1st pass
 *
 * @param line the line string
 * @param il1 the instruction list
 * @param dl the data list
 * @param sl the symbol list
 * @param eh the error handler
 */
void parse_line(char *line, instruction_list_pass1 *il1, data_list *dl, symbol_list *sl, error_handler *eh);

/**
 * @brief fill all symbols of instructions in the 2nd pass
 *
 * @param inst_list a pointer to the array of pointers to instructions to fill
 * @param il1 the instruction list from 1st pass
 * @param sl the symbol list
 * @param el the external list
 * @param eh the error handler
 * @return int the length of the instruction list
 */
int fill_symbols(instruction_pass2 ***inst_list, instruction_list_pass1 *il1, symbol_list *sl, external_list *el, error_handler *eh);

#endif