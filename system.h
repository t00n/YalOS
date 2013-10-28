#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stdbool.h> // type bool
#include <stddef.h> // size_t
#include <stdint.h>

// Copy from src to dest in memory
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);

// Assign val to dest[count] in memory
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);

// Assign val 16-bit to dest[count] in memory
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

// Return length of str
extern size_t strlen(const char *str);

// Get 1 byte from I/O device
extern unsigned char inportb (unsigned short _port);

// Put 1 byte to I/O device
extern void outportb (unsigned short _port, unsigned char _data);

#endif
