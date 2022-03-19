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

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        char *fname = strconcat(argv[i], ".as");
        FILE *fp = fopen(fname, "r");
        if(fp) {

        char line[MAX_LINE + 1];
        symbol_list *sl = sl_create();
        instruction_list_pass1 *il1 = il1_create();
        data_list *dl = dl_create();

        instruction_pass2 **inst_list;
        int length;
        external_list *el = el_create();

        preassembler_parse_file(fp, argv[i]);
        fclose(fp);

        fname = strconcat(argv[i], ".am");
        fp = fopen(fname, "r");

        while (fgets(line, MAX_LINE + 1, fp))
        {
            parse_line(line, il1, dl, sl);
        }

        sl_update_data_address(sl, il1_get_ic(il1));

        length = fill_symbols(&inst_list, il1, sl, el);

        write_entries(argv[i], sl);
        write_externs(argv[i], el);
        write_objects(argv[i], inst_list, length, dl, il1_get_ic(il1));

        fclose(fp);
        } else {
            printf("Can't open file %s\n", fname);
        }
        free(fname);

    }
    return 0;
}