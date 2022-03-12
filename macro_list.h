#ifndef MACRO_LIST_H
#define MACRO_LIST_H

typedef struct macro macro;
void m_append(macro *m, char *line);
macro *m_create(char *name);
char *m_get_line(macro *m, int i);

typedef struct macro_list macro_list;
macro_list *ml_create();
void ml_append(macro_list *list, macro *m);
macro * ml_get(macro_list *list, char *name);

#endif
