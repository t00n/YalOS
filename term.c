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
	memsetw(term_buffer, term_mkentry(' ', term_color), TERM_HEIGHT*TERM_WIDTH);
	term_mvcrs();
}

void term_clrr(size_t row)
{
	memsetw(term_buffer+row*TERM_WIDTH, term_mkentry(' ', term_color), TERM_WIDTH);
	term_mvcrs();
}
 
void term_putc(char c)
{
	const size_t index = term_row * TERM_WIDTH + term_column;
	if (c == '\n')
	{
		term_putnl();
	}
	else if (c == '\r')
	{
		term_column = 0;
	}
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == '\t')
    {
        term_column = (term_column + 4) & ~(4 - 1);
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
				term_column = TERM_WIDTH - 1;
			}		
		}
		term_buffer[index] = term_mkentry(' ', term_color);
	}
	else
	{
		term_buffer[index] = term_mkentry(c, term_color);
		++term_column;
	}
	term_scroll();
	term_mvcrs();
}

void term_putsc(const char* s, uint8_t color)
{
	uint8_t old_color = term_color;
	term_color = color;
	term_puts(s);
	term_color = old_color;
}
 
void term_puts(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		term_putc(data[i]);
}

void term_putnl()
{
	term_column = 0;
	++term_row;	
}

void term_mvcrs()
{
	size_t index = term_row * TERM_WIDTH + term_column;
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

void term_scroll()
{
	if ( term_column == TERM_WIDTH )
	{
		term_putnl();
	}	
	if ( term_row == TERM_HEIGHT )
	{
		// move buffer one line up
		memcpy((unsigned char *)term_buffer, (unsigned char *) term_buffer+TERM_WIDTH*2, (TERM_HEIGHT-1)*TERM_WIDTH*2);
		--term_row;
		// clean last line
        memsetw (term_buffer + (TERM_HEIGHT-1) * TERM_WIDTH, term_mkentry(' ', term_color), TERM_WIDTH);
	}
}
