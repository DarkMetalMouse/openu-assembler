/**
 * @file data_list.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 *
 * API for data list
 */
#ifndef _DATA_LIST_H
#define _DATA_LIST_H

#include <stdint.h>

typedef struct data_list
{
    int dc;
    int data_size;
    uint16_t *bytes;
} data_list;

/**
 * @brief create a new data list object
 *
 * @return data_list* a new data list
 */
data_list *dl_create();

/**
 * @brief append a number to a data list
 *
 * @param dl the data list
 * @param num the value to append
 */
void dl_append_num(data_list *dl, int16_t num);

/**
 * @brief append a string to a data list
 *
 * @param dl the data list
 * @param s the string to append
 */
void dl_append_string(data_list *dl, char *s);

/**
 * @brief read value from data list
 * use dl_get_dc to get the length
 *
 * @param dl the data list
 * @param i the index to read at
 * @return uint16_t the value at that index
 */
uint16_t dl_get_val(data_list *dl, int i);

/**
 * @brief get the length of filled spaces in the data list
 *
 * @param dl the data list
 * @return int the length (data counter)
 */
int dl_get_dc(data_list *dl);

/**
 * @brief free the memory used by the data list
 *
 * @param dl the data list to free
 */
void dl_destroy(data_list *dl);

#endif