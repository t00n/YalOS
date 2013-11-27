#ifndef __KB_H
#define __KB_H

#include "irq.h"
#include "shell.h"


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

enum keybinding {
	CTRL = 1,
	LEFT_SHIFT = 2,
	RIGHT_SHIFT = 3,
	ALT = 4,
	CAPS_LOCK = 5,
	NUM_LOCK = 6,
	SCROLL_LOCK = 7,
	F1 = 65,
	F2 = 66,
	F3 = 67,
	F4 = 68,
	F5 = 69,
	F6 = 70,
	F7 = 71,
	F8 = 72,
	F9 = 73,
	F10 = 74,
	F11 = 75,
	F12 = 76,
	PRINT = '*',
	HOME = 77,
	PG_UP = 78,
	END = 79,
	PG_DOWN = 80,
	INSERT = 81,
	DELETE = 82,
	ARROW_UP = 83,
	ARROW_LEFT = 84,
	ARROW_RIGHT = 85,
	ARROW_DOWN = 86
};

unsigned char kbdus[256];
struct keystate keys;

void keyboard_handler(struct regs *r);
void keyboard_install();

#endif
