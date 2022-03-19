#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_list.h"
#include "instruction_list_pass1.h"
#include "operand.h"
#include "symbol_list.h"
#include "util.h"
#include "opcode.h"
#include "instruction_pass2.h"
#include "writer.h"

symbol *parse_symbol_attribute(char *line, symbol_attribute attribute)
{
    symbol *s;
    char *name;
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
        sl_append(sl, parse_symbol_attribute(line + 6, ENTRY)); /* 6 == strlen(".entry") */
        return;
    }
    else if (starts_with_word(line, ".extern"))
    {
        sl_append(sl, parse_symbol_attribute(line + 7, EXTERNAL)); /* 7 == strlen(".extern") */
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

        if (s)
        {
            s_set_type(s, DATA);
            s_set_address(s, dl_get_dc(dl));
        }

        line += 5;
        number = strtok(line, ",");
        add_int(number, dl);
        while (NULL != (number = strtok(NULL, ",")))
        {
            add_int(number, dl);
        }
    }
    else if (starts_with_word(line, ".string"))
    {
        char *end;

        if (s)
        {
            s_set_type(s, DATA);
            s_set_address(s, dl_get_dc(dl));
        }

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
    }
    else /* code */
    {
        char *part;
        int i = 0;
        operand operands[MAX_OPERAND_COUNT];
        opcode opcode;

        if (s)
        {
            s_set_type(s, CODE);
            s_set_address(s, il1_get_ic(il1));
        }

        line += skip_spaces(line);
        part = get_next_word(line);
        line += strlen(part);
        opcode = get_opcode(part);
        free(part);

        if (opcode == -1)
        {
            /* ERROR ILLEGAL OPCODE */
            return;
        }

        line += skip_spaces(line);
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
    }
    if (s)
        sl_append(sl, s);
}

instruction_pass2 *fill_symbol(instruction_pass1 *inst, symbol_list *sl, external_list *el, int *ic)
{
    int i;
    (*ic)++;
    if (inst->operand_count)
    {
        (*ic)++;
    }
    for (i = 0; i < inst->operand_count; i++)
    {
        address *address = NULL;
        if (inst->operands[i].type == indexed)
        {
            address = &inst->operands[i].data_type.indexed.address;
        }
        else if (inst->operands[i].type == direct)
        {
            address = &inst->operands[i].data_type.address;
        }
        if (address != NULL)
        {
            symbol *s = sl_get(sl, (*address).pass1);
            if (s_get_attribute(s) == EXTERNAL)
            {
                (*address).pass2.is_external = 1;
                el_append(el, e_create(s_get_name(s), *ic));
            }
            else
            {
                (*address).pass2.is_external = 0;
            }
            (*address).pass2.value = s_get_address(s);
        }
        *ic += get_operand_size(inst->operands[i]);
    }

    return i_create(inst->opcode, inst->operand_count, inst->operands);
}

int fill_symbols(instruction_pass2 ***inst_list, instruction_list_pass1 *il1, symbol_list *sl, external_list *el)
{
    int length = il1_get_length(il1), i, ic = 100;
    instruction_pass1 *inst;
    *inst_list = malloc(i2_size() * length);
    inst = il1_get_head(il1);

    for (i = 0; i < length; i++)
    {
        (*inst_list)[i] = fill_symbol(inst, sl, el, &ic);

        inst = i1_get_next(inst);
    }
    return length;
}

/* int main(int argc, char const *argv[])
{
    FILE *fp = fopen("ps.as", "r");
    char line[MAX_LINE + 1];
    symbol_list *sl = sl_create();
    instruction_list_pass1 *il1 = il1_create();
    data_list *dl = dl_create();
    external_list *el = el_create();
    instruction_pass2 **inst_list;
    int length;

    while (fgets(line, MAX_LINE + 1, fp))
    {
        parse_line(line, il1, dl, sl);
    }

    sl_update_data_address(sl, il1_get_ic(il1));

    length = fill_symbols(&inst_list, il1, sl, el);

    write_entries("ps", sl);
    write_externs("ps", el);
    write_objects("ps", inst_list, length, dl, il1_get_ic(il1));

    fclose(fp);
    return 0;
} */
