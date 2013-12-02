#include "shell.h"

bool shell_quit = false;
struct shell_command shell_cmd[10];

void reboot()
{
	outportb(0x64, 0xFE);	
}

void shell_init()
{
	shell_cmd[0].name = "reboot";
	shell_cmd[0].function = &reboot;
	shell_wait_cmd();
}

void shell_wait_cmd()
{
	shell_wait = true;
	shell_index = 0;
	memset((unsigned char*)shell_buffer, 0, SHELL_WIDTH);
	term_putc('>');
}

void shell_loop()
{
	while (shell_quit == false)
	{
		if (shell_wait == true)
		{
			shell_wait = true;
		}
		else
		{
			shell_parse();
			shell_wait_cmd();
		}
	}
}

void shell_char(struct keystate keys)
{
	if (keys.keychar == '\n')
	{
		shell_wait = false;
		term_putc(keys.keychar);
	}
	else if (keys.keychar == '\b')
	{
		if (shell_index > 0)
		{
			--shell_index;
			shell_buffer[shell_index] = 0;
			term_putc(keys.keychar);
		}
	}
	else if (shell_index < SHELL_WIDTH)
	{
		shell_buffer[shell_index] = keys.keychar;
		++shell_index;
		term_putc(keys.keychar);
	}
}

void shell_parse()
{
	for (int i = 0; i < 10; ++i)
	{
		if (strdiff(shell_buffer, shell_cmd[i].name) == 0)
		{
			shell_cmd[i].function();
		}
	}
}
