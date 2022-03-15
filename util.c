#include <stdlib.h>
#include <string.h>
#include "util.h"

char* dupstr(char *s) 
{
    char *copy = malloc(sizeof(char) * MAX_LINE);
    strcpy(copy, s);
    return copy;
}

int skip_spaces(char *s)
{
    int i = 0;
    for (i = 0; i < MAX_LINE && !isspace(s[i]) && i != '\0'; i++)
        ;
    return i;
}

int is_last_word(char *s)
{
    int i = 0;
    while (isalnum(s[i]))
    {
        i++;
    }
    while (s[i] != '\0')
    {
        if (!isspace(s[i]))
            return 0;
        i++;
    }
    return 1;
}

void trim_word(char *s)
{
    int i = 0;
    while (isalnum(s[i]))
    {
        i++;
    }
    s[i] = '\0';
}

int starts_with_word(char*s, char* word) 
{
    int len = strlen(word);
    return strncmp(s, word, len) == 0 && strlen(s) > 6 && isspace(s + len);
}