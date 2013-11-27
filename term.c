#include "term.h"

uint8_t term_mkcolor(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t term_mkentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
void term_init()
{
	term_row = 0;
	term_column = 0;
	term_color = term_mkcolor(COLOR_LIGHT_GREY, COLOR_BLACK);
	term_buffer = (uint16_t*) 0xB8000;
	term_clr();
}

void term_clr()
{
	memsetw(term_buffer, term_mkentry(' ', term_color), VGA_HEIGHT*VGA_WIDTH);
	term_mvcrs();
}
 
void term_putc(char c)
{
	if (c == '\n')
	{
		term_newline();
	}
	else if (c == '\r')
	{
		term_column = 0;
	}
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == '\t')
    {
        term_column = (term_column + 8) & ~(8 - 1);
    }
	else if (c == '\b')
	{
		if (term_column > 0)
		{
			--term_column;
		}
		else
		{
			if (term_row > 0)
			{
				--term_row;
				term_column = VGA_WIDTH - 1;
			}		
		}
		size_t index = term_row*VGA_WIDTH + term_column;
		term_buffer[index] = term_mkentry(' ', term_color);
	}
	else
	{
		const size_t index = term_row * VGA_WIDTH + term_column;
		term_buffer[index] = term_mkentry(c, term_color);
		++term_column;
	}
	term_scroll();
	term_mvcrs();
}
 
void term_puts(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		term_putc(data[i]);
}

void term_mvcrs()
{
	size_t index = term_row * VGA_WIDTH + term_column;
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

void term_scroll()
{
	if ( term_column == VGA_WIDTH )
	{
		term_newline();
	}	
	if ( term_row == VGA_HEIGHT )
	{
		// move buffer one line up
		memcpy((unsigned char *)term_buffer, (unsigned char *) term_buffer+VGA_WIDTH*2, (VGA_HEIGHT-1)*VGA_WIDTH*2);
		--term_row;
		// clean last line
        memsetw (term_buffer + (VGA_HEIGHT-1) * VGA_WIDTH, term_mkentry(' ', term_color), VGA_WIDTH);
	}
}

void term_newline()
{
	term_column = 0;
	++term_row;	
}
