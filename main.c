/**
 * @file main.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 *
 * The main program, it runs the preassembler, 1st pass, 2nd pass and file writing.
 * Mostly following the algorithem skeleton
 */

#include <stdio.h>
#include <stdlib.h>
#include "symbol_list.h"
#include "instruction_list_pass1.h"
#include "data_list.h"
#include "instruction_pass2.h"
#include "writer.h"
#include "util.h"
#include "parser.h"
#include "preassembler.h"
#include "error_handler.h"

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        char *fname = strconcat(argv[i], ".as");
        FILE *fp = fopen(fname, "r");
        if (fp)
        {
            int i;

            error_handler *eh = eh_create();

            char line[MAX_LINE + 1];
            symbol_list *sl = sl_create();
            instruction_list_pass1 *il1 = il1_create();
            data_list *dl = dl_create();

            instruction_pass2 **inst_list;
            int length;
            external_list *el = el_create();

            printf("parsing %s\n", fname);

            preassembler_parse_file(fp, argv[i]);
            fclose(fp);

            free(fname);
            fname = strconcat(argv[i], ".am");
            fp = fopen(fname, "r");

            while (fgets(line, MAX_LINE + 1, fp))
            {
                parse_line(line, il1, dl, sl, eh);
                eh_next_line(eh);
            }

            /* update data list with icf */
            sl_update_data_address(sl, il1_get_ic(il1));

            length = fill_symbols(&inst_list, il1, sl, el, eh);

            if (!eh_had_error(eh))
            {
                write_entries(argv[i], sl);
                write_externs(argv[i], el);
                write_objects(argv[i], inst_list, length, dl, il1_get_ic(il1));
            }

            fclose(fp);
            free(eh);
            sl_destroy(sl);
            il1_destroy(il1);
            dl_destroy(dl);
            el_destroy(el);
            for (i = 0; i < length; i++)
            {
                i_destroy(inst_list[i]);
            }
            free(inst_list);
        }
        else
        {
            printf("Can't open file %s\n", fname);
        }
        free(fname);
    }
    return 0;
}