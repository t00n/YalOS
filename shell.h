#ifndef __SHELL_H
#define __SHELL_H
#include "kb.h"
#include "term.h"

#define SHELL_WIDTH 79

char shell_buffer[SHELL_WIDTH];
size_t shell_index;
bool shell_wait;
bool shell_quit;
void** shell_cmd;

struct keystate;

void shell_char(struct keystate keys);
void shell_loop();
void shell_init();
void shell_parse();

#endif
