#ifndef __SHELL_H
#define __SHELL_H
#include "kb.h"
#include "term.h"

unsigned char shell_buffer[80];
int shell_wait;

void shell_char(unsigned char c);
void shell_loop();
void shell_initialize();

#endif
