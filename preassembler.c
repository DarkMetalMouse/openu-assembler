#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "macro_list.h"
#include "util.h"




char *get_file_name(char *name)
{
    char *new_name = malloc(strlen(name) + 4); /*  sizeof (.am\0) == 4 */
    strcpy(new_name, name);
    strcat(new_name, ".am");
    return new_name;
}

FILE *parsefile(FILE *fp, char name[])
{
    macro_list *macros = ml_create();
    char line[MAX_LINE + 1];
    int in_macro = 0;
    macro *m;
    char *fname = get_file_name(name);
    FILE *out = fopen(fname, "w");
    while (NULL != fgets(line, MAX_LINE, fp))
    {
        int i = 0;
        int len;
        i = skip_spaces(line);
        len = strlen(&line[i]);
        if (in_macro)
        {
            if (strncmp(&line[i], "endm", 4) == 0 && is_last_word(&line[i]))
            {
                ml_append(macros, m);
                in_macro = 0;
            }
            else
            {
                m_append(m, line);
                fwrite(line, 1, strlen(line), out);
            }
        }
        else if (starts_with_word(&line[i],"macro"))
        {
            i += 6;
            trim_word(&line[i]);
            m = m_create(&line[i]);
            in_macro = 1;
        }
        else
        {
            if (is_last_word(&line[i]))
            {
                macro *found_macro;
                trim_word(&line[i]);
                found_macro = ml_get(macros, &line[i]);
                if (found_macro != NULL)
                {
                    int i = 0;
                    char *m_line;
                    while ((m_line = m_get_line(found_macro, i++)) != NULL)
                    {
                        fwrite(m_line, 1, strlen(m_line), out);
                    }
                }
                else
                {
                    fwrite(line, 1, strlen(line), out);
                }
            }
            else
            {
                fwrite(line, 1, strlen(line), out);
            }
        }
    }
    ml_destroy(macros);
    free(fname);
    return out;
}

/*int main(int argc, char const *argv[])
{
    FILE *fp = fopen("preassembler_test_1.txt", "r");
    parsefile(fp, "preassembler");
    return 0;
}*/
