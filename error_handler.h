#ifndef _ERROR_HANDLER_H
#define _ERROR_HANDLER_H

#include <stdarg.h>

typedef struct error_handler
{
    int line;
    int had_error;
} error_handler;

error_handler *eh_create();
void eh_next_line(error_handler *eh);
int eh_had_error(error_handler *eh);

typedef enum error_type
{
    OPERAND_COUNT_MISMATCH, /* inc r3, r2 */
    EXTERN_DEFINED_IN_FILE, /* .extern SYMBOL ... SYMBOL: .data 6,-9 */
    DUPLICATE_LABEL,        /* SYMBOL: .data 6,-9 ... SYMBOL: inc r3 */
    EXTERNAL_AND_ENTRY,     /* .extern SYMBOL ... .entry SYMBOL */
    NOT_A_NUMBER,           /* #hello */
    NUMBER_OUT_OF_RANGE,    /* #100000000 */
    UNKNOWN_REGISTER,       /* SYMBOL[r100] */
    ILLEGAL_ARGUMENT,       /* SYMBOL hello || SYMBOL */
    NOT_A_STRING,           /* .string "hello */
    UNKNOWN_OPCODE,         /* run r1,r2 */
    EXTRANOUS_TEXT
} error_type;

void error(error_handler *eh, error_type type, ...);

#endif