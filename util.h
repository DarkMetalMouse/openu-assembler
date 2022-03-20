/**
 * @file util.h
 * @author DarkMetalMouse
 * @date 2022-03-20
 * Utility functions, mostly for handling strings
 */

#ifndef _UTIL_H
#define _UTIL_H

#define MAX_LINE 80
#define WITHIN(val, min, max) ((min) <= (val) && (val) <= (max))

/**
 * @brief duplicate a string
 *
 * @param s the string
 * @return char* the new string
 */
char *dupstr(char *s);

/**
 * @brief get the index of the first non space character
 *
 * @param s the string
 * @return int the index
 */
int skip_spaces(char *s);

/**
 * @brief check if the sequence of chars at the start of the string is followed by spaces only
 *
 * @param s the string
 * @return int whether its the last word in the string
 */
int is_last_word(char *s);

/**
 * @brief remove trailing spaces from string
 *
 * @param s the string
 */
void trim_word(char *s);

/**
 * @brief check if a string starts with a given word
 *
 * @param s the string
 * @param word the word
 * @return int whether the string starts with the word
 */
int starts_with_word(char *s, char *word);

/**
 * @brief copy the next word of the string
 *
 * @param line the string
 * @return char* the next word
 */
char *get_next_word(char *line);

/**
 * @brief concatnate new strings into a new one
 *
 * @param s1 the first string
 * @param s2 the second string
 * @return char* the new string
 */
char *strconcat(char *s1, char *s2);

#endif