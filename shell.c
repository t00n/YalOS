#include "shell.h"

int shell_wait = 1;

void shell_initialize()
{
	memset(shell_buffer, 0, 80);
}

void shell_loop()
{
	while (true)
	{
		if (shell_wait == 1)
		{
			terminal_move_cursor();
		}
		else
		{
			terminal_writestring("cmd ok\n");
			terminal_putchar('>');
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
	terminal_putchar(c);
}

//~ void shell_input(char* s, size_t l)
//~ {
	//~ memcpy(shell_buffer, s, l);
	//~ shell_wait = 0;
//~ }
