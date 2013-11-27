#include "shell.h"

void shell_init()
{
	shell_wait = true;
	shell_index = 0;
	memset((unsigned char*)shell_buffer, 0, SHELL_WIDTH);
	term_putc('>');
}

void shell_loop()
{
	while (true)
	{
		if (shell_wait == true)
		{
			term_scroll();
		}
		else
		{
			shell_init();
		}
	}
}

void shell_char(char c)
{
	if (c == '\n')
	{
		shell_wait = false;
		term_putc(c);
	}
	else if (c == '\b')
	{
		if (shell_index > 0)
		{
			--shell_index;
			shell_buffer[shell_index] = 0;
			term_putc(c);
		}
	}
	else if (shell_index < SHELL_WIDTH)
	{
		shell_buffer[shell_index] = c;
		++shell_index;
		term_putc(c);
	}
}
