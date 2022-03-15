#ifndef _UTIL_H
#define _UTIL_H

#define MAX_LINE 80

char* dupstr(char *s);
int skip_spaces(char *s);
int is_last_word(char *s);
void trim_word(char *s);
int starts_with_word(char*s, char* word);

#endif