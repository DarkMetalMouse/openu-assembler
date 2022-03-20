/**
 * @file operand.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * The operand implementation
 */

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
    operand o;
    o.data_type.imm = value;
    o.type = immidiate;
    return o;
}

operand o_create_index_1(char *symbol, unsigned int r)
{
    operand o;
    o.data_type.indexed.address.pass1 = dupstr(symbol);
    o.data_type.indexed.reg = r;
    o.type = indexed;
    return o;
}

operand o_create_direct_1(char *symbol)
{
    operand o;
    o.data_type.address.pass1 = dupstr(symbol);
    o.type = direct;
    return o;
}

operand o_create_reg(unsigned int r)
{
    operand o;
    o.data_type.reg = r;
    o.type = reg;
    return o;
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

operand parse_operand(char *s, error_handler *eh)
{
    int reg = -1;
    s += skip_spaces(s);
    if (!is_last_word(s))
    {
        error(eh, ILLEGAL_ARGUMENT, 1, s);
        return o_create_immidiate(0);
    }

    trim_word(s);
    if (s[0] == '#')
    {

        long num;
        char *extra;
        s++;
        num = strtol(s, &extra, 10);
        if (extra[0] != '\0')
        {
            error(eh, NOT_A_NUMBER,1, s);
            return o_create_immidiate(0);
        }
        else if (num > INT16_MAX || num < INT16_MIN)
        {
            error(eh, NUMBER_OUT_OF_RANGE,1, s);
            return o_create_immidiate(0);
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
                char *r;
                s[strlen(s) - 1] = '\0';
                s[i] = '\0';
                r = s + i + 1;
                r += skip_spaces(r);

                trim_word(r);
                if (-1 != (reg = get_reg(r)))
                {
                    return o_create_index_1(s, reg);
                }
                else
                {
                    error(eh, UNKNOWN_REGISTER,1, r);
                    return o_create_index_1(s, 0);
                }
            }
            else
            {
                o_create_index_1("", 0);
            }
        }
    }
    return o_create_immidiate(0); /* we shouldn't get here anyways*/
}