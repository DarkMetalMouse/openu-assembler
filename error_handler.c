/**
 * @file error_handler.c
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Implementation of error handling
 */

#include "error_handler.h"
#include <stdlib.h>
#include <stdio.h>

#define ERROR_SIZE 256

error_handler *eh_create()
{
    error_handler *eh = malloc(sizeof(error_handler));
    eh->line = 1;
    eh->had_error = 0;
    return eh;
}

void eh_next_line(error_handler *eh)
{
    eh->line++;
}

int eh_get_line(error_handler *eh)
{
    return eh->line;
}

void eh_set_line(error_handler *eh, int line)
{
    eh->line = line;
}

int eh_had_error(error_handler *eh)
{
    return eh->had_error;
}

void error(error_handler *eh, error_type type, int count, ...)
{
    va_list ap;
    eh->had_error = 1;
    printf("ERROR in line %d: ", eh->line);
    va_start(ap, count);
    switch (type)
    {
    case OPERAND_COUNT_MISMATCH:
        printf("Incorrect number of arguments\n");
        break;
    case EXTERN_DEFINED_IN_FILE:
        printf("Symbol can't be external and defined in the file at the same time\n");
        break;
    case DUPLICATE_LABEL:
        printf("Duplicate symbol\n");
        break;
    case EXTERNAL_AND_ENTRY:
        printf("Symbol can't be external and entry in the same file\n");
        break;
    case NOT_A_NUMBER:
        printf("\"%s\" is not a number\n", va_arg(ap, char *));
        break;
    case NUMBER_OUT_OF_RANGE:
        printf("\"%s\" must be a signed 16 bit integer\n", va_arg(ap, char *));
        break;
    case UNKNOWN_REGISTER:
        printf("Unknown register \"%s\"\n", va_arg(ap, char *));
        break;
    case ILLEGAL_ARGUMENT:
        printf("Illegal argument \"%s\"\n", va_arg(ap, char *));
        break;
    case NOT_A_STRING:
        printf(".string must be followed by a double quoted string\n");
        break;
    case UNKNOWN_OPCODE:
        printf("Unknown opcode \"%s\"\n", va_arg(ap, char *));
        break;
    case EXTRANOUS_TEXT:
        printf("Extranous text\n");
        break;
    case UNDEFINED_SYMBOL:
        printf("Symbol \"%s\" referenced but not defined\n", va_arg(ap, char *));
        break;
    case INVALID_SYMBOL:
        printf("Symbol name is illegal: \"%s\"\n", va_arg(ap, char *));
        break;
    case ILLEGAL_OPERAND_TYPE:
        printf("Illegal operand type\n");
        break;
    default:
        printf("error\n");
        break;
    }
}