#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_list.h"
#include "util.h"

#define INITIAL_LINE_COUNT 20


typedef struct macro
{
    char *name;
    char **lines;
    int line_count;
    int lines_filled;
    macro *next;
} macro;

typedef struct macro_list
{
    macro *head;
    macro *tail;

} macro_list;

macro *m_create(char name[])
{
    macro *m = malloc(sizeof(macro));
    m->name = dupstr(name);
    m->lines = malloc(sizeof(char *) * INITIAL_LINE_COUNT);
    m->line_count = INITIAL_LINE_COUNT;
    m->lines_filled = 0;
    m->next = NULL;

    return m;
}

void m_append(macro *m, char *line)
{
    if (m->lines_filled == m->line_count)
    {
        m->line_count *= 2;
        m->lines = realloc(m->lines, m->line_count);
    }

    m->lines[m->lines_filled++] = dupstr(line);
}

char *m_get_line(macro *m, int i)
{
    if (i > m->lines_filled)
        return NULL;
    return m->lines[i];
}

macro_list *ml_create()
{
    macro_list *list = malloc(sizeof(macro_list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void ml_append(macro_list *list, macro *m)
{
    if (list->head == NULL)
    {
        list->head = m;
        list->tail = m;
        return;
    }
    list->tail->next = m;
    list->tail = m;
}

macro *ml_get(macro_list *list, char *name)
{
    macro *ptr = list->head;
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

void m_destroy(macro *m)
{
    int i = 0;
    char *line;
    while ((line = m_get_line(m, i)) != NULL)
    {
        free(line);
        i++;
    }
    free(m->lines);
    free(m->name);
    free(m);
}

void ml_destroy(macro_list *list)
{
    macro *ptr = list->head;
    macro *tmp;
    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        m_destroy(tmp);
    }
    free(list);
}
