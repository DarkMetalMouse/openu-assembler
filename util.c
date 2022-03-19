#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

char *dupstr(char *s)
{
    char *copy = malloc(sizeof(char) * MAX_LINE);
    strcpy(copy, s);
    return copy;
}

int skip_spaces(char *s)
{
    int i = 0;
    for (i = 0; i < MAX_LINE && isspace(s[i]) && s[i] != '\0'; i++)
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
    while (s[i] != '\0' && !isspace(s[i]))
    {
        i++;
    }
    if (!(s[i] == '\0')) /* prevent segfault if there aren't any spaces*/
    {
        s[i] = '\0';
    }
}

int starts_with_word(char *s, char *word)
{
    int len = strlen(word);
    return strncmp(s, word, len) == 0 && strlen(s) > 6 && isspace(*(s + len));
}

char *get_next_word(char *line)
{
    char *word = NULL;
    int i = 0;
    while (line[i] != '\0' && !isspace(line[i]))
    {
        i++;
    }
    if (i > 0)
    {
        word = malloc(sizeof(char) * i);
        strncpy(word, line, i);
        word[i] = '\0';
    }
    return word;
}

char *get_next_num(char *line)
{
    char *word;
    int i = 0;
    while (isdigit(line[i]))
    {
        i++;
    }
    word = malloc(sizeof(char) * i);
    strncpy(word, line, i - 1);
    word[i] = '\0';

    return word;
}

char *strconcat(char *s1, char *s2)
{
    char *new_s = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(new_s, s1);
    strcat(new_s, s2);
    return new_s;
}