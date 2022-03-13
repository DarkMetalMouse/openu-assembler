#include <stdlib.h>
#include <string.h>
#include "util.h"

char* dupstr(char *s) 
{
    char *copy = malloc(sizeof(char) * MAX_LINE);
    strcpy(copy, s);
    return copy;
}
