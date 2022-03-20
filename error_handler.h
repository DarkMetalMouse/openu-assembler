/**
 * @file error_handler.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Error handler using one fuction to handle all errors
 */

#ifndef _ERROR_HANDLER_H
#define _ERROR_HANDLER_H

#include <stdarg.h>

typedef struct error_handler
{
    int line;
    int had_error;
} error_handler;

/**
 * @brief create a new error handler object
 *
 * @return error_handler* a new error handler
 */
error_handler *eh_create();

/**
 * @brief increment the line counter
 *
 * @param eh the error handler
 */
void eh_next_line(error_handler *eh);

/**
 * @brief get current line
 *
 * @param eh the error handler
 * @return int the current line
 */
int eh_get_line(error_handler *eh);

/**
 * @brief set the current line - useful for 2nd pass
 *
 * @param eh the error handler
 * @param line the line number to set
 */
void eh_set_line(error_handler *eh, int line);

/**
 * @brief check if the error handler caught an error before
 *
 * @param eh the error handler
 * @return int if the error handler caught an error before
 */
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
    EXTRANOUS_TEXT,         /* .string "hello" abc */
    UNDEFINED_SYMBOL,       /* inc HI */
    INVALID_SYMBOL,         /* 1aa: || a-f: || aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: */
    ILLEGAL_OPERAND_TYPE    /* inc #48 */
} error_type;

/**
 * @brief report an error to the error handler
 *
 * @param eh the error handler
 * @param type the type of the error
 * @param count the number of custom arguments
 * @param ... the custom arguments of the errors formatstring
 */
void error(error_handler *eh, error_type type, int count, ...);

#endif