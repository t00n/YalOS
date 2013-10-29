#include "term.h"

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	terminal_clear();
}

void terminal_clear()
{
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
	terminal_move_cursor();
}
 
void terminal_putchar(char c)
{
	if (c == '\n')
	{
		terminal_newline();
	}
	else if (c == '\r')
	{
		terminal_column = 0;
	}
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == '\t')
    {
        terminal_column = (terminal_column + 8) & ~(8 - 1);
    }
	else if (c == '\b')
	{
		if (terminal_column > 0)
		{
			--terminal_column;
		}
		else
		{
			if (terminal_row > 0)
			{
				--terminal_row;
				terminal_column = VGA_WIDTH - 1;
			}		
		}
		size_t index = terminal_row*VGA_WIDTH + terminal_column;
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
	else
	{
		const size_t index = terminal_row * VGA_WIDTH + terminal_column;
		terminal_buffer[index] = make_vgaentry(c, terminal_color);
		++terminal_column;
	}
	terminal_scroll();
	terminal_move_cursor();
}
 
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

void terminal_move_cursor()
{
	size_t index = terminal_row * VGA_WIDTH + terminal_column;
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

void terminal_scroll()
{
	if ( terminal_column == VGA_WIDTH )
	{
		terminal_newline();
	}	
	if ( terminal_row == VGA_HEIGHT )
	{
		// move buffer one line up
		memcpy((unsigned char *)terminal_buffer, (unsigned char *) terminal_buffer+VGA_WIDTH*2, (VGA_HEIGHT-1)*VGA_WIDTH*2);
		--terminal_row;
		// clean last line
        memsetw (terminal_buffer + (VGA_HEIGHT-1) * VGA_WIDTH, make_vgaentry(' ', terminal_color), VGA_WIDTH);
	}
}

void terminal_newline()
{
	terminal_column = 0;
	++terminal_row;	
}
