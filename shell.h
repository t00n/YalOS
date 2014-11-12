#ifndef __SHELL_H
#define __SHELL_H
#include "kb.h"
#include "vga.h"

#define SHELL_WIDTH 79

struct shell_command
{
	char* name;
	void (*function)(int argc, char** argv);
};

char shell_buffer[SHELL_WIDTH];
size_t shell_index;
bool shell_wait;
bool shell_quit;
struct shell_command shell_cmd[10];

struct keystate;

void shell_char(struct keystate keys);
void shell_loop();
void shell_init();
void shell_wait_cmd();
void shell_parse();

#endif
