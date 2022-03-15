#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "symbol_list.h"

typedef struct symbol
{
    char *name;
    address address;
    symbol_type type;
    symbol_attribute attribute;
    struct symbol *next;

} symbol;

typedef struct symbol_list
{
    symbol *head;
    symbol *tail;
} symbol_list;


symbol *s_create(char *name, uint16_t address, symbol_type type, symbol_attribute attribute) {
    symbol *s = malloc(sizeof(symbol));
    s->name = dupstr(name);
    s->address.value = address;
    s->type = type;
    s->attribute = attribute;
    s->next = NULL;
    return s;
}

void *s_set_name(symbol *s, char *name) {
    s->name = dupstr(name);
}

void s_set_type(symbol *s, symbol_type type) {
    s->type = type;
}

void sl_append(symbol_list *sl, symbol *s) {
    symbol *ptr;
    if(sl->head == NULL) {
        sl->head = s;
        sl->tail = s;
        return;
    }

    ptr = sl->head;
    while (ptr != NULL)
    {
        if(strcmp(ptr->name,s->name) == 0) {
            if (s->address.value != 0)
            {
                if(ptr->attribute == EXTERNAL) {
                    /* ERROR EXTENTAL CANNOT BE DEFINED INTARNALLY */
                }
                if (ptr->address.value == 0) {
                    ptr->address = s->address;
                    ptr-> type = s->type; /* if we know the address we know the type */
                } else {
                    /* ERROR DUPLICATE LABEL*/
                }
            } else {
                /* if no address was supplied, it must be a ".entry SYMBOL" or ".extern SYMBOL" */
                
                if ((s->attribute | ptr->attribute) == 3) /* 01|10 == 11 */
                {
                     /* ERROR SYMBOL CANNOT BE BOTH EXTENTAL AND INTERNAL */
                } else { /* 00|XX, XX|XX */
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

symbol *sl_get(symbol_list *sl, char * name) {
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

symbol_list *sl_create() {
    symbol_list *sl= malloc(sizeof(symbol_list));
    sl->head = NULL;
    sl->tail = NULL;
    return sl;
}

void s_destroy(symbol *s) {
    free(s->name);
    free(s);
}

void sl_destroy(symbol_list *sl) {
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


int main(int argc, char const *argv[])
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
