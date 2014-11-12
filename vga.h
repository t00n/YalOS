#ifndef __VGA_H
#define __VGA_H

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
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t vga_row;
size_t vga_column;
uint8_t vga_color;
uint16_t* vga_buffer;

uint8_t vga_mkcolor(enum vga_color fg, enum vga_color bg);
uint16_t vga_mkentry(char c, uint8_t color);

void vga_init();
void vga_setpos(size_t col, size_t row);

void vga_putc(char c);
void vga_puts(const char* data);
void vga_putsc(const char* s, uint8_t color);
void vga_putnl();
void vga_clr();
void vga_clrr(size_t row);

void vga_scroll();
void vga_mvcrs();

#endif // __VGA_H
