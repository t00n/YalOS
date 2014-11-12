#include "vga.h"

uint8_t vga_mkcolor(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t vga_mkentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
void vga_init()
{
	vga_color = vga_mkcolor(COLOR_LIGHT_GREY, COLOR_BLACK);
	vga_buffer = (uint16_t*) 0xB8000;
	vga_clr();
}

void vga_setpos(size_t col, size_t row)
{
	if (col < VGA_WIDTH && row < VGA_HEIGHT)
	{
		vga_row = row;
		vga_column = col;
		vga_mvcrs();
	}
}

void vga_clr()
{
	memsetw(vga_buffer, vga_mkentry(' ', vga_color), VGA_HEIGHT*VGA_WIDTH);
	vga_setpos(0,0);
}

void vga_clrr(size_t row)
{
	if (row < VGA_HEIGHT)
	{
		memsetw(vga_buffer+row*VGA_WIDTH, vga_mkentry(' ', vga_color), VGA_WIDTH);
		vga_setpos(row, 0);
	}
}
 
void vga_putc(char c)
{
	if (c == '\n')
	{
		vga_putnl();
	}
	else if (c == '\r')
	{
		vga_column = 0;
	}
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == '\t')
    {
        vga_column = (vga_column + 4) & ~(4 - 1);
    }
	else if (c == '\b')
	{
		if (vga_column > 0)
		{
			--vga_column;
		}
		else
		{
			if (vga_row > 0)
			{
				--vga_row;
				vga_column = VGA_WIDTH - 1;
			}		
		}
		const size_t index = vga_row * VGA_WIDTH + vga_column;
		vga_buffer[index] = vga_mkentry(' ', vga_color);
	}
	else
	{
		const size_t index = vga_row * VGA_WIDTH + vga_column;
		vga_buffer[index] = vga_mkentry(c, vga_color);
		++vga_column;
	}
	vga_scroll();
	vga_mvcrs();
}
 
void vga_puts(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		vga_putc(data[i]);
}

void vga_putsc(const char* s, uint8_t color)
{
	uint8_t old_color = vga_color;
	vga_color = color;
	vga_puts(s);
	vga_color = old_color;
}

void vga_putnl()
{
	vga_column = 0;
	++vga_row;	
}

void vga_mvcrs()
{
	size_t index = vga_row * VGA_WIDTH + vga_column;
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

void vga_scroll()
{
	if ( vga_column == VGA_WIDTH )
	{
		vga_putnl();
	}	
	if ( vga_row == VGA_HEIGHT )
	{
		// move buffer one line up
		memcpy((unsigned char *)vga_buffer, (unsigned char *) vga_buffer+VGA_WIDTH*2, (VGA_HEIGHT-1)*VGA_WIDTH*2);
		--vga_row;
		// clean last line
        memsetw (vga_buffer + (VGA_HEIGHT-1) * VGA_WIDTH, vga_mkentry(' ', vga_color), VGA_WIDTH);
	}
}
