#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_list.h"
#include "instruction_list.h"
#include "instruction.h"
#include "operand.h"
#include "symbol_list.h"
#include "util.h"

char *get_next_word(char *line)
{
    char *word;
    int i = 0;
    while (!isspace(line[i]))
    {
        i++;
    }
    word = malloc(sizeof(char) * i);
    strncpy(word, line, i - 1);
    word[i] = '\0';
    return word;
}

char *get_next_num(char *line)
{
    char *word;
    int i = 0;
    while (isdigit(line[i]))
    {
        i++;
    }
    word = malloc(sizeof(char) * i);
    strncpy(word, line, i - 1);
    word[i] = '\0';

    return word;
}

symbol *parse_symbol_attribute(char *line, symbol_attribute attribute)
{
    symbol *s;
    char name;
    line += 6; /* 6 == strlen(".entry") */
    name = get_next_word(line);
    if (is_last_word(line))
    {
        s = s_create(get_next_word(line), 0, UNKNOWN, attribute);
        free(name);
        return s;
    }
    else
    {
        return NULL;
    }
}

symbol *get_symbol_instantiation(char *line)
{
    symbol *s;
    int i = 0;
    while (line[i] != ':' && line[i] != '\0')
    {
        i++;
    }
    if (line[i] == '\0')
    { /* not a symbol definition */
        return NULL;
    }
    line[i] = '\0'; /* "MAIN: mov r3,16" -> "MAIN" */
    s = s_create(line, 0, UNKNOWN, NONE);
    line[i] = ':';
    if (s == NULL)
    {
        return NULL;
    }
    return s;
}

void parse_line(char *line, instruction_list *il, data_list *dl, symbol_list *sl)
{
    int len;
    symbol *s;
    line = &line[skip_spaces(line)];
    len = strlen(line);
    if (len > 0 && line[0] == ';') /* comment line */
        return;
    if (starts_with_word(line, ".entry"))
    {
        sl_append(sl, parse_symbol_attribute(line, ENTRY));
        return;
    }
    else if (starts_with_word(line, ".extern"))
    {
        sl_append(sl, parse_symbol_attribute(line, EXTERNAL));
        return;
    }
    else if ((s = get_symbol_instantiation(line)))
    {
        line += s_get_name_length(s) + 1; /* "MAIN" -> " mov r3,16"*/
        line = &line[skip_spaces(line)];
    }
    if (starts_with_word(line, ".data") || starts_with_word(line, ".string"))
    {
        char *number;
        if (s)
            s_set_type(s, DATA);
    }
    else
    {
        if (s)
            s_set_type(s, CODE);
    }
}

int main(int argc, char const *argv[])
{
    /*     parse_symbol(dupstr("\t \t\t.entry\tLIST\t\t"), 0);
        parse_symbol(dupstr("\t \t\t.extern  \tval1   "), 0);
        parse_symbol(dupstr("LIST: .data 9,-6"), 0); */
    return 0;
}
