#include "shell.h"

bool shell_quit = false;
struct shell_command shell_cmd[10];

void reboot(int argc, char** argv)
{
	outportb(0x64, 0xFE);	
}

void echo(int argc, char** argv)
{
	int len = argc, i;
	for (i = 1; i < len; ++i)
	{
		vga_puts(argv[i]);
		vga_putc(' ');
	}
	vga_putnl();
}

void shell_init()
{
	shell_cmd[0].name = "reboot";
	shell_cmd[0].function = &reboot;
	shell_cmd[1].name = "echo";
	shell_cmd[1].function = &echo;
	shell_wait_cmd();
}

void shell_wait_cmd()
{
	shell_wait = true;
	shell_index = 0;
	memset((unsigned char*)shell_buffer, 0, SHELL_WIDTH);
	vga_putc('>');
}

void shell_loop()
{
	while (shell_quit == false)
	{
		if (shell_wait == true)
		{
			__asm__ __volatile("nop");
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
		vga_putc(keys.keychar);
	}
	else if (keys.keychar == '\b')
	{
		if (shell_index > 0)
		{
			--shell_index;
			shell_buffer[shell_index] = 0;
			vga_putc(keys.keychar);
		}
	}
	else if (shell_index < SHELL_WIDTH)
	{
		shell_buffer[shell_index] = keys.keychar;
		++shell_index;
		vga_putc(keys.keychar);
	}
}

void shell_parse()
{
	// bool done = false;
	// char ** parse = malloc(50);
	// int count = strsplit(shell_buffer, ' ', parse);
	// for (int i = 0; i < 10; ++i)
	// {
	// 	if (strdiff(parse[0], shell_cmd[i].name) == 0)
	// 	{
	// 		shell_cmd[i].function(count, parse);
	// 		done = true;
	// 	}
	// }
	// if (! done)
	// {
	// 	vga_puts("Unknown command\n");
	// }
}
