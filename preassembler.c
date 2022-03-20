/**
 * @file preassembler.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Full implimentation of preassember
 * It does not check for error as there isn't any required error parsing at this stage
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "macro_list.h"
#include "util.h"

void preassembler_parse_file(FILE *fp, char name[])
{
    macro_list *macros = ml_create();
    char line[MAX_LINE + 1];
    int in_macro = 0;
    macro *m;
    char *fname = strconcat(name, ".am");
    FILE *out = fopen(fname, "w");
    while (NULL != fgets(line, MAX_LINE, fp))
    {
        int i = 0;
        i = skip_spaces(line);
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
        else if (starts_with_word(&line[i], "macro"))
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
                char *copy = dupstr(&line[i]);
                trim_word(copy);
                found_macro = ml_get(macros, copy);
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
    fclose(out);
}
