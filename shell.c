#include "shell.h"

void shell_init()
{
	shell_wait = 1;
	shell_index = 0;
	memset(shell_buffer, 0, 80);
	term_putc('>');
}

void shell_loop()
{
	while (true)
	{
		if (shell_wait == 1)
		{
			term_scroll();
		}
		else
		{
			term_puts(shell_buffer); // out
			term_putc('\n');
			shell_init();
		}
	}
}

void shell_char(unsigned char c)
{
	term_putc(c);
	if (c == '\n')
	{
		shell_wait = 0;
	}
	else if (c == '\b')
	{
		--shell_index;
		shell_buffer[shell_index] = 0;
	}
	else
	{
		shell_buffer[shell_index] = c;
		++shell_index;
	}
}
