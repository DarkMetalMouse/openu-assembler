#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_list.h"
#include "instruction_list_pass1.h"
#include "instruction_pass2.h"
#include "operand.h"
#include "symbol_list.h"
#include "util.h"

symbol *parse_symbol_attribute(char *line, symbol_attribute attribute)
{
    symbol *s;
    char *name;
    line += 6; /* 6 == strlen(".entry") */
    line += skip_spaces(line);
    name = get_next_word(line);
    if (is_last_word(line))
    {
        s = s_create(name, 0, UNKNOWN, attribute);
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

void add_int(char *number, data_list *dl)
{
    long num;
    char *extra;
    number += skip_spaces(number);
    trim_word(number);
    num = strtol(number, &extra, 10);
    if (extra[0] != '\0')
    {
        /* ERROR NOT A NUMBER */
    }
    else if (num > INT16_MAX || num < INT16_MIN)
    {
        /* ERROR NUM MUST BE A 16 BIT INTEGER */
    }
    else
    {
        dl_append_num(dl, (int16_t)num);
    }
}

void parse_line(char *line, instruction_list_pass1 *il1, data_list *dl, symbol_list *sl)
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
    if (starts_with_word(line, ".data"))
    {
        char *number;

        line += 5;
        number = strtok(line, ",");
        add_int(number, dl);
        while (NULL != (number = strtok(NULL, ",")))
        {
            add_int(number, dl);
        }
        if (s)

        {
            s_set_type(s, DATA);
            s_set_address(s, dl_get_dc(dl));
        }
    }
    else if (starts_with_word(line, ".string"))
    {
        char *end;
        line += 7;
        line += skip_spaces(line);
        if (line[0] != '"')
        {
            /*ERROR NOT A STRING*/
            return;
        }
        line++;

        if (NULL != (end = strchr(line, '"')))
        {

            *end = '\0';
            dl_append_string(dl, line);
        }

        if (s)
        {
            s_set_type(s, DATA);
            s_set_address(s, dl_get_dc(dl));
        }
    }
    else
    {
        char *part;
        int i = 0;
        operand operands[MAX_OPERAND_COUNT];
        opcode opcode;
        line += skip_spaces(line);
        part = get_next_word(line); /* TODO: parse stop correctly */
        line += strlen(part);
        opcode = get_opcode(part);
        free(part);

        if (opcode == -1)
        {
            /* ERROR ILLEGAL OPCODE */
            return;
        }

        part = strtok(line, ",");
        if (part) /* first arg */
        {
            operands[i++] = parse_operand(part);
            part = strtok(NULL, ",");

            if (part) /* second arg */
            {
                operands[i++] = parse_operand(part);
            }
        }
        if (strtok(NULL, ",") != NULL) /* third arg (error) */
        {
            /* ERROR TOO MANY ARGUMENTS */
        }

        il1_append(il1, i1_create(opcode, operands, i));

        if (s)
        {
            s_set_type(s, CODE);
            s_set_address(s, il1_get_ic(il1));
        }
    }
    if (s)
        sl_append(sl, s);
}

int main(int argc, char const *argv[])
{
    symbol_list *sl = sl_create();
    instruction_list_pass1 *il1 = il1_create();
    data_list *dl = dl_create();
    /*     parse_line(dupstr("LIST: .data 9,-6"), il1, dl, sl);
        parse_line(dupstr("SYMBOL: .data 1,2,2"), il1, dl, sl);
        parse_line(dupstr("\t \t\t.entry\tLIST\t\t"), il1, dl, sl);
        parse_line(dupstr(".string \"Hello, World!\""), il1, dl, sl); */
    parse_line(dupstr("add r3, LIST"), il1, dl, sl);
    parse_line(dupstr("prn #48"), il1, dl, sl);
    parse_line(dupstr("lea STR, r6"), il1, dl, sl);
    parse_line(dupstr("inc r6"), il1, dl, sl);
    parse_line(dupstr("mov r3, W"), il1, dl, sl);
    parse_line(dupstr("sub r1, r4"), il1, dl, sl);
    parse_line(dupstr("bne END"), il1, dl, sl);
    parse_line(dupstr("cmp val1, #-6"), il1, dl, sl);
    parse_line(dupstr("bne END[r15]"), il1, dl, sl);
    parse_line(dupstr("dec K"), il1, dl, sl);
    parse_line(dupstr("sub LOOP[r10] ,r14"), il1, dl, sl);
    parse_line(dupstr("stop"), il1, dl, sl);

    return 0;
}
