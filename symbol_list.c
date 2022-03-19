#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#include "symbol_list.h"

#define MAX_SYMBOL_LENGTH 31

int is_legal_symbol_name(char *name)
{
    int len = strlen(name);
    int i;
    if (len == 0)
        return 0;
    if (!isalpha(name[0]))
        return 0;
    for (i = 1; i < len; i++)
    {
        if (!isalnum(name[i]))
            return 0;
    }
    if (i > MAX_SYMBOL_LENGTH)
    {
        return 0;
    }
    return 1;
}

int s_set_name(symbol *s, char *name)
{
    if (name == NULL)
    {
        return 1;
    }

    if (!is_legal_symbol_name(name))
    {
        s_destroy(s);
        return 0;
    }
    s->name = dupstr(name);
    return 1;
}
symbol *s_create(char *name, uint16_t address, symbol_type type, symbol_attribute attribute)
{
    symbol *s = malloc(sizeof(symbol));
    if (!s_set_name(s, name))
    {
        return NULL;
        s_destroy(s);
    }
    s->address = address;
    s->type = type;
    s->attribute = attribute;
    s->next = NULL;
    return s;
}

int s_get_name_length(symbol *s)
{
    return strlen(s->name);
}
symbol_attribute s_get_attribute(symbol *s)
{
    return s->attribute;
}

uint16_t s_get_address(symbol *s)
{
    return s->address;
}

char *s_get_name(symbol *s)
{
    return s->name;
}

void s_set_type(symbol *s, symbol_type type)
{
    s->type = type;
}

void s_set_address(symbol *s, uint16_t address)
{
    s->address = address;
}

void sl_append(symbol_list *sl, symbol *s)
{
    symbol *ptr;

    if (s == NULL)
        return;
    if (sl->head == NULL)
    {
        sl->head = s;
        sl->tail = s;
        return;
    }

    ptr = sl->head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, s->name) == 0)
        {
            if (s->address != 0)
            {
                if (ptr->attribute == EXTERNAL)
                {
                    /* ERROR EXTENTAL CANNOT BE DEFINED INTARNALLY */
                }
                if (ptr->address == 0)
                {
                    ptr->address = s->address;
                    ptr->type = s->type; /* if we know the address we know the type */
                }
                else
                {
                    /* ERROR DUPLICATE LABEL*/
                }
            }
            else
            {
                /* if no address was supplied, it must be a ".entry SYMBOL" or ".extern SYMBOL" */

                if ((s->attribute | ptr->attribute) == 3) /* 01|10 == 11 */
                {
                    /* ERROR SYMBOL CANNOT BE BOTH EXTENTAL AND INTERNAL */
                }
                else
                { /* 00|XX, XX|XX */
                    ptr->attribute = s->attribute;
                }
            }

            s_destroy(s);
            return; /* modified symbol */
        }
        ptr = ptr->next;
    }

    sl->tail->next = s;
    sl->tail = s;
}

symbol *sl_get(symbol_list *sl, char *name)
{
    symbol *ptr = sl->head;
    while (ptr != NULL)
    {
        if (strcmp(name, ptr->name) == 0)
        {
            return ptr;
        }
        ptr = ptr->next;
    }

    return NULL;
}

symbol_list *sl_create()
{
    symbol_list *sl = malloc(sizeof(symbol_list));
    sl->head = NULL;
    sl->tail = NULL;
    return sl;
}

void s_destroy(symbol *s)
{
    free(s->name);
    free(s);
}

void sl_destroy(symbol_list *sl)
{
    symbol *ptr = sl->head;
    symbol *tmp;
    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        s_destroy(tmp);
    }
    free(sl);
}
void sl_update_data_address(symbol_list *sl, uint16_t icf)
{
    symbol *ptr = sl->head;
    while (ptr != NULL)
    {
        if (ptr->type == DATA)
        {
            ptr->address += icf;
        }

        ptr = ptr->next;
    }
}

symbol *get_entry(symbol *s)
{
    while (s != NULL)
    {
        if (s->attribute == ENTRY)
        {
            return s;
        }

        s = s->next;
    }
    return NULL;
}

symbol *sl_get_entry(symbol_list *sl)
{
    return get_entry(sl->head);
}
symbol *s_get_entry(symbol *s)
{
    return get_entry(s->next);
}

/*int main(int argc, char const *argv[])
{
    symbol_list *list = sl_create();
    symbol *s = s_create("LIST", 0, UNKNOWN, ENTRY);
    sl_append(list,s);
    s = s_create("W", 0, UNKNOWN, EXTERNAL);
    sl_append(list,s);
    s = s_create("MAIN", 100, CODE, NONE);
    sl_append(list,s);
    s = s_create("LOOP", 104, CODE, NONE);
    sl_append(list,s);
    s = s_create("MAIN", 0, UNKNOWN, ENTRY);
    sl_append(list,s);
    s = s_create("END", 140, CODE, NONE);
    sl_append(list,s);
    s = s_create("STR", 141, DATA, NONE);
    sl_append(list,s);
    s = s_create("LIST", 146, DATA, NONE);
    sl_append(list,s);
    s = s_create("K", 0, UNKNOWN, ENTRY);
    sl_append(list,s);
    s = s_create("K", 149, DATA, EXTERNAL);
    sl_append(list,s);
    sl_append(list,s);
    s = s_create("val1", 0, UNKNOWN, EXTERNAL);
    sl_append(list,s);

    sl_destroy(list);
    return 0;
}
*/