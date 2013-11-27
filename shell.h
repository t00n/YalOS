#ifndef __SHELL_H
#define __SHELL_H
#include "kb.h"
#include "term.h"

#define SHELL_WIDTH 78

char shell_buffer[SHELL_WIDTH];
size_t shell_index;
int shell_wait;
void** shell_cmd;

void shell_char(char c);
void shell_loop();
void shell_init();

#endif
