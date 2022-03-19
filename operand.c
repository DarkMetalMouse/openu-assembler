#include "operand.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int OPERAND_SIZE[] = {1, 2, 2, 0};

int get_operand_size(operand operand)
{
    return OPERAND_SIZE[operand.type];
}

operand o_create_immidiate(int16_t value)
{
    return (operand){.data_type.imm = value, .type = immidiate};
}

operand o_create_index_2(uint16_t address, unsigned int r, int is_external)
{
    return (operand){.data_type.indexed.address.pass2.is_external = is_external, //
                     .data_type.indexed.address.pass2.value = address,           //
                     .data_type.indexed.reg = r,                                 //
                     .type = indexed};
}

operand o_create_direct_2(uint16_t address, int is_external)
{
    return (operand){.data_type.address.pass2.is_external = is_external, //
                     .data_type.address.pass2.value = address,           //
                     .type = direct};
}

operand o_create_index_1(char *symbol, unsigned int r)
{
    return (operand){.data_type.indexed.address.pass1 = symbol, //
                     .data_type.indexed.reg = r,                //
                     .type = indexed};
}

operand o_create_direct_1(char *symbol)
{
    return (operand){.data_type.address.pass1 = symbol, //
                     .type = direct};
}

operand o_create_reg(unsigned int r)
{
    return (operand){.data_type.reg = r, .type = reg};
}

int get_reg(char *s)
{
    if (s[0] == '\0' || s[0] != 'r'       /* W */
        || s[1] == '\0' || !isdigit(s[1]) /* rA */
    )
    {
        return -1;
    }

    if (s[2] == '\0') /* r9 */
    {
        return s[1] - '0'; /* '7' -> 7 */
    }
    if (s[1] == '1' && WITHIN(s[2], '0', '5') && s[3] == '\0')
    {                             /* r15 */
        return 10 + (s[2] - '0'); /* "15" -> 10 + 5 */
    }

    return -1;
}

operand parse_operand(char *s)
{
    int reg = -1;
    s += skip_spaces(s);
    trim_word(s);
    if (s[0] == '#')
    {

        long num;
        char *extra;
        s++;
        num = strtol(s, &extra, 10);
        if (extra[0] != '\0')
        {
            /* ERROR NOT A NUMBER */
        }
        else if (num > INT16_MAX || num < INT16_MIN)
        {
            /* ERROR NUM MUST BE A 16 BIT INTEGER */
        }
        else
        {
            return o_create_immidiate((int16_t)num);
        }
    }
    else if (-1 != (reg = get_reg(s)))
    {
        return o_create_reg(reg);
    }
    else
    {
        int i = 0;
        while (s[i] != '\0' && s[i] != '[' && !isspace(s[i])) /* ABC || ABC[... || ABC [...*/
        {
            i++;
        }

        if (s[i] == '\0') /* direct */
        {
            return o_create_direct_1(s);
        }
        else /* index */
        {

            if (s[strlen(s) - 1] == ']') /* ABC[...] */
            {
                s[strlen(s) - 1] = '\0';
                s[i] = '\0';
                char *r = s + i + 1;
                r += skip_spaces(r);
                if (is_last_word(r))
                {
                    trim_word(r);
                    if (-1 != (reg = get_reg(r)))
                    {
                        return o_create_index_1(s, reg);
                    }
                }
                else
                {
                    /* ERROR ILLEGAL ARGUMENT */
                }
            }
            else
            {
                /* ILLEGAL ARGUMENT ERROR */
            }
        }
    }
    return (operand){.data_type = -1, .data_type.imm = 0};
}