#include "system.h"

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	for (int i = 0; i < count; ++i)
	{
		dest[i] = src[i];
	}
	return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    for (int i = 0; i < count; ++i)
    {
		dest[i] = val;
	}
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    for (int i = 0; i < count; ++i)
    {
		dest[i] = val;
	}
	return dest;
}

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
