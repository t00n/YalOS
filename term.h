#ifndef __TERM_H
#define __TERM_H

#include "system.h"
#include "string.h"

enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
static const size_t TERM_WIDTH = 80;
static const size_t TERM_HEIGHT = 25;
 
size_t term_row;
size_t term_column;
uint8_t term_color;
uint16_t* term_buffer;

uint8_t term_mkcolor(enum vga_color fg, enum vga_color bg);
uint16_t term_mkentry(char c, uint8_t color);

void term_init();
void term_setpos(size_t col, size_t row);

void term_putc(char c);
void term_puts(const char* data);
void term_putsc(const char* s, uint8_t color);
void term_putnl();
void term_clr();

void term_scroll();
void term_mvcrs();

#endif // __TERM_H
