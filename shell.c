#include "shell.h"

int shell_wait = 1;
int shell_index = 0;

void shell_init()
{
	memset(shell_buffer, 0, 80);
}

void shell_loop()
{
	while (true)
	{
		if (shell_wait == 1)
		{
			term_scroll();
			term_mvcrs();
		}
		else
		{
			term_puts("cmd ok\n");
			term_putc('>');
			shell_wait = 1;
		}
		//~ shell_wait = 1;			
	}
}

void shell_char(unsigned char c)
{
	if (c == '\n')
	{
		shell_wait = 0;
	}
	term_putc(c);
}
