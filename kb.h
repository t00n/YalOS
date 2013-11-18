#ifndef __KB_H
#define __KB_H

#include "irq.h"
#include "term.h"


struct keystatus {
	int alt;
	int ctrl;
	int shift;
	int capslock;
	int numlock;
	int scrolllock;
};

unsigned char kbdus[128];
void keyboard_handler(struct regs *r);
void keyboard_install();

#endif
