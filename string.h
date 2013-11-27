#ifndef __STRING_H
#define __STRING_H
#include "system.h"

// Return length of str
size_t strlen(const char *str);

// Return number of differences between 2 strings
int strdiff(const char* s1, const char* s2);

// Return index of first different character. >0 if s1>s2.
int strcmp(const char* s1, const char* s2);


#endif
