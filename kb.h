#ifndef __KB_H
#define __KB_H

#include "irq.h"
#include "term.h"


struct keystate {
	int ctrl;
	int left_shift;
	int right_shift;
	int alt;
	int capslock;
	int numlock;
	int scrolllock;
	char keychar;
};

unsigned char kbdus[256];
struct keystate keys;

void keyboard_handler(struct regs *r);
void keyboard_install();

#endif
