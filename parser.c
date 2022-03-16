#include <stdlib.h>
#include <string.h>
#include "symbol_list.h"
#include "util.h"

symbol *parse_symbol(char *line, int address)
{
    symbol *s = NULL;
    int i = 0;
    line = &line[skip_spaces(line)];
    if (starts_with_word(line, ".entry"))
    {
        s = s_create(NULL, 0, UNKNOWN, ENTRY);
        line += 6; /* strlen(".entry") */
    }
    else if (starts_with_word(line, ".extern"))
    {
        s = s_create(NULL, 0, UNKNOWN, EXTERNAL);
        line += 7; /* strlen(".extern") */
    }
    if (s)
    {
        line = &line[skip_spaces(line)];
        if (is_last_word(line))
        {
            trim_word(line);

            if (s_set_name(s, line))
                return s;
            else
                return NULL; /* ILLEGAL NAME*/
        }
        else
        {
            /* ERROR TOO MANY ARGUMENTS*/
        }
    }
    while (line[i] != ':' && line[i] != '\0')
    {
        i++;
    }
    if (line[i] == '\0')
    { /* not a symbol definition */
        return NULL;
    }
    line[i] = '\0'; /* "MAIN: mov r3,16" -> "MAIN" */
    s = s_create(line, address, UNKNOWN, NONE);
    if (s == NULL)
    {
        return NULL;
    }

    line += i + 1; /* "MAIN" -> " mov r3,16"*/
    line = &line[skip_spaces(line)];

    if (starts_with_word(line, ".data") || starts_with_word(line, ".string"))
    {
        s_set_type(s, DATA);
    }
    else
    {
        s_set_type(s, CODE);
    }

    return s;
}

int main(int argc, char const *argv[])
{
    parse_symbol(dupstr("\t \t\t.entry\tLIST\t\t"), 0);
    parse_symbol(dupstr("\t \t\t.extern  \tval1   "), 0);
    parse_symbol(dupstr("LIST: .data 9,-6"), 0);
    return 0;
}
