#include <stdlib.h>
#include <ctype.h>
#include "instruction.h"
#include "operand.h"
#include "instruction_list.h"
#include "symbol_list.h"
#include "data_list.h"
#include "util.h"

int is_legal_symbol_name(char *name) {
    int len = strlen(name);
    int i;
    if(len == 0) 
        return 0;
    if(!isalpha(name[0]))
        return 0;
    for ( i = 1; i < len; i++)
    {
        if(!isalnum(name[i]))
            return 0;
    }
    return 1;

    
}


symbol *parse_symbol(char *line, int address) {
    symbol *s = NULL;
    int i = 0;
    line = &line[skip_spaces(line)];
    if(starts_with_word(line,".entry")) {
        s = s_create("", 0, UNKNOWN, ENTRY);
        line += 6; /* strlen(".entry") */
    } else if (starts_with_word(line, ".extern")) {
        s = s_create("", 0, UNKNOWN, EXTERNAL);
        line+= 7; /* strlen(".extern") */
    }
    if(s) {
        line = &line[skip_spaces(line)];
        if (is_last_word(line)) {
            trim_word(line);
            if(is_legal_symbol_name(line)) 
            {
            s_set_name(s,line);
            } else {
                /* ERROR ILLEGAL SYMBOL NAME */
            }
            return;
        } else {
            /* ERROR TOO MANY ARGUMENTS*/
        }
    } 
    while (line[i] != ':' && line[i] != '\0')
    {
        i++;
    }
    if(line[i] == '\0') { /* not a symbol definition */
        return NULL;
    }
    line[i] = '\0'; /* "MAIN: mov r3,16" -> "MAIN" */
    if(!is_legal_symbol_name(line)) {
        /* ERROR ILLEGAL SYMBOL NAME */
        return NULL;
    }
    s = s_create(line, address, UNKNOWN, NONE);
    line++; /* "MAIN" -> " mov r3,16"*/
    line = &line[skip_spaces(line)];


    if(starts_with_word(line,".data") || starts_with_word(line, ".string")) {
        s_set_type(s,DATA); 
    } else {
        s_set_type(s,CODE); 
    }

    return s;
}