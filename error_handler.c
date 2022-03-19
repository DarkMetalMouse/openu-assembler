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

int eh_had_error(error_handler *eh)
{
    return eh->had_error;
}

void error(error_handler *eh, error_type type, ...)
{
    /* char buf[ERROR_SIZE]; */
    eh->had_error = 1;
    printf("ERROR in line %d: ", eh->line);

    switch (type)
    {
    case OPERAND_COUNT_MISMATCH:
        printf("Instruction takes %%d arguments but %%d were given\n");
        break;
    case EXTERN_DEFINED_IN_FILE:
        printf("Symbol can't be external and defined in the file at the same time");
        break;
    case DUPLICATE_LABEL:
        printf("Duplicate symbol\n");
        break;
    case EXTERNAL_AND_ENTRY:
        printf("Symbol can't be external and entry in the same file\n");
        break;
    case NOT_A_NUMBER:
        printf("\"%%d\" is not a number\n");
        break;
    case NUMBER_OUT_OF_RANGE:
        printf("\"%%d\" must be a signed 16 bit integer\n");
        break;
    case UNKNOWN_REGISTER:
        printf("Unknown register \"%%s\"");
        break;
    case ILLEGAL_ARGUMENT:
        printf("Illegal argument \"%%s\"");
        break;
    case NOT_A_STRING:
        printf(".string must be followed by a double quoted string\n");
        break;
    case UNKNOWN_OPCODE:
        printf("Unknown opcode\n");
        break;
    case EXTRANOUS_TEXT:
        printf("Extranous text\n");
        break;

    default:
        printf("error\n");
        break;
    }
}