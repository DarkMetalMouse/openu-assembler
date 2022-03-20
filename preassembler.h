/**
 * @file preassembler.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * preassembler api
 */

#ifndef _PREASSEMBLER_H
#define _PREASSEMBLER_H

/**
 * @brief write a new file with the macros layed out
 *
 * @param fp the file top parse
 * @param name the name of the file
 */
void preassembler_parse_file(FILE *fp, char name[]);

#endif