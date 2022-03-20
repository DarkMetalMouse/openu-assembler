/**
 * @file macro_list.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * List of macros contating each macro name and code
 */

#ifndef MACRO_LIST_H
#define MACRO_LIST_H

typedef struct macro
{
    char *name;
    char **lines;
    int line_count;
    int lines_filled;
    struct macro *next;
} macro;

/**
 * @brief create a new macro
 *
 * @param name the name of the macro
 * @return macro* a new macro
 */
macro *m_create(char *name);

/**
 * @brief apppend a line to the macro
 *
 * @param m the macro
 * @param line the line
 */
void m_append(macro *m, char *line);

/**
 * @brief get a line of a macro
 * if no line exists at the index NULL is returned
 *
 * @param m the macro
 * @param i the index of the line
 * @return char* the line
 */
char *m_get_line(macro *m, int i);

/**
 * @brief free the memory used by a macro
 *
 * @param m the macro
 */
void m_destroy(macro *m);

typedef struct macro_list
{
    macro *head;
    macro *tail;

} macro_list;

/**
 * @brief create a new macro list
 *
 * @return macro_list* a new macro list
 */
macro_list *ml_create();

/**
 * @brief append a macro to the list
 *
 * @param list the macro list
 * @param m the macro
 */
void ml_append(macro_list *list, macro *m);

/**
 * @brief get a macro from the list using its name
 *
 * @param list the list
 * @param name the name of the desired macro
 * @return macro* the relevant macro
 */
macro *ml_get(macro_list *list, char *name);

/**
 * @brief free the memory used by the macro list
 * 
 * @param list the macro list list
 */
void ml_destroy(macro_list *list);

#endif
