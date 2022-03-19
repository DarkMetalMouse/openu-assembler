#ifndef _PARSER_H
#define _PARSER_H
#include "symbol_list.h"
#include "instruction_list_pass1.h"
#include "data_list.h"
#include "instruction_pass2.h"
#include "writer.h"

void parse_line(char *line, instruction_list_pass1 *il1, data_list *dl, symbol_list *sl);
int fill_symbols(instruction_pass2 ***inst_list, instruction_list_pass1 *il1, symbol_list *sl, external_list *el);

#endif