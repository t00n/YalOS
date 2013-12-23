#ifndef __STRING_H
#define __STRING_H
#include "system.h"
#include "memory.h"

// Return length of str
size_t strlen(const char *str);

// Return number of differences between 2 strings
int strdiff(const char* s1, const char* s2);

// Return index of first difference between 2 strings.
int strcmp(const char* s1, const char* s2);

// return number of substrings
int strsplit(const char* s, char limit, char** ret);

#endif
