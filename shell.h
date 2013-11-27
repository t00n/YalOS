#ifndef __SHELL_H
#define __SHELL_H
#include "kb.h"
#include "term.h"

unsigned char shell_buffer[80];
int shell_index;
int shell_wait;
void** shell_cmd;

void shell_char(unsigned char c);
void shell_loop();
void shell_init();

#endif
