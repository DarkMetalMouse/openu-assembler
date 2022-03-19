#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instruction_pass2.h"
#include "data_list.h"
#include "symbol_list.h"
#include "util.h"
#include "writer.h"

typedef struct external_value
{
    char *name;
    uint16_t address;
    struct external_value *next;
} external_value;

typedef struct external_list
{
    external_value *head;
    external_value *tail;
} external_list;

external_value *e_create(char *name, uint16_t address)
{
    external_value *e = malloc(sizeof(external_value));
    e->name = name;
    e->address = address;
    return e;
}

external_list *el_create()
{
    external_list *el = malloc(sizeof(external_list));
    el->head = NULL;
    el->tail = NULL;
    return el;
}

void el_append(external_list *el, external_value *e)
{
    if (el->head == NULL)
    {
        el->head = e;
        el->tail = e;
        return;
    };
    el->tail->next = e;
    el->tail = e;
}

void write_entries(char *fname, symbol_list *sl)
{
    FILE *fp;
    symbol *s;
    char line[81];
    fname = strconcat(fname, ".ent");
    fp = fopen(fname, "w");
    s = sl_get_entry(sl);

    while (s)
    {
        uint16_t address = s_get_address(s);
        sprintf(line, "%s,%d,%d\n", s_get_name(s), address & 0xF0, address & 0x0F);
        fwrite(line, sizeof(char), strlen(line), fp);
        s = s_get_entry(s);
    }
    fclose(fp);
}

void write_externs(char *fname, external_list *el)
{
    FILE *fp;
    external_value *e;
    char line[81];
    fname = strconcat(fname, ".ext");
    fp = fopen(fname, "w");
    e = el->head;
    while (e)
    {
        sprintf(line, "%s BASE %d\n", e->name, e->address);
        fwrite(line, sizeof(char), strlen(line), fp);
        sprintf(line, "%s OFFSET %d\n\n", e->name, e->address + 1);
        fwrite(line, sizeof(char), strlen(line), fp);
        e = e->next;
    }
    fclose(fp);
}

void obj_write_line(FILE *fp, uint32_t value, int line_num)
{
    char line[81];

    sprintf(line,
            "%04d\tA%x-B%x-C%x-D%x-E%x\n",
            line_num,
            (value & 0xF0000) >> 16,
            (value & 0x0F000) >> 12,
            (value & 0x00F00) >> 8,
            (value & 0x000F0) >> 4,
            (value & 0x0000F) >> 0);
    fwrite(line, sizeof(char), strlen(line), fp);
}

void write_objects(char *fname, instruction_pass2 **inst_list, int inst_count, data_list *dl)
{
    FILE *fp;
    int i, j, line_num = 100;
    fname = strconcat(fname, ".ob");
    fp = fopen(fname, "w");

    for (i = 0; i < inst_count; i++)
    {
        for (j = 0; j < i_get_size(inst_list[i]); j++)
        {
            obj_write_line(fp, i_get_word(inst_list[i], j), line_num++);
        }
    }
    for (i = 0; i < dl_get_dc(dl); i++)
    {
        obj_write_line(fp, dl_get_val(dl, i) | (0x40000), line_num++);
        /* 0x40000 because data is always absolute */
    }

    fclose(fp);
}

void write_files(char *fname, instruction_pass2 **inst_list, data_list *dl, symbol_list *sl)
{
}