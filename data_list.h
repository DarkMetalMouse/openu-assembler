#ifndef _DATA_LIST_H
#define _DATA_LIST_H

#include <stdint.h>

typedef struct data_list
{
    int dc;
    int data_size;
    uint16_t *bytes;
} data_list;

data_list *dl_create();
void dl_append_num(data_list *dl, int16_t num);
void dl_append_string(data_list *dl, char *s);
uint16_t dl_get_val(data_list *dl, int i);
int dl_get_dc(data_list *dl);
void dl_destroy(data_list *dl);

#endif