#include "kb.h"

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[256] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    CTRL,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`'/*(²)*/,   LEFT_SHIFT,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   RIGHT_SHIFT,				/* Right shift */
  PRINT/*printscreen*/,
    ALT,	/* Alt */
  ' ',	/* Space bar */
    CAPS_LOCK,	/* Caps lock */
    F1,	/* 59 - F1 key ... > */
    F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,
    F10,	/* < ... F10 */
    NUM_LOCK,	/* 69 - Num lock*/
    SCROLL_LOCK,	/* Scroll Lock */
    HOME,	/* Home key */
    ARROW_UP,	/* Up Arrow */
    PG_UP,	/* Page Up */
  '-',
    ARROW_LEFT,	/* Left Arrow */
    0,/* NUMPAD 5 */
    ARROW_RIGHT,	/* Right Arrow */
  '+',
    END,	/* 79 - End key*/
    ARROW_DOWN,	/* Down Arrow */
    PG_DOWN,	/* Page Down */
    INSERT,	/* Insert Key */
    DELETE,	/* Delete Key */
    0,   0,   '<',
    F11,	/* F11 Key */
    F12,	/* F12 Key */
    0,	/* 89 - All other keys are undefined */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0/*128*/, 27,
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', /* Digits */'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', CTRL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', LEFT_SHIFT, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', RIGHT_SHIFT, PRINT, ALT, ' ', CAPS_LOCK, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUM_LOCK, SCROLL_LOCK, HOME, ARROW_UP, PG_UP, '-', ARROW_LEFT, 0, ARROW_RIGHT, '+', END, ARROW_DOWN, PG_DOWN, INSERT, DELETE, 0, 0, '>', F11, F12, 0
};


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode, key;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
		key = kbdus[scancode & 0x7F];
		switch (key)
		{
			case 1:
				keys.ctrl = 0;
				break;
			case 2:
				keys.left_shift = 0;
				break;
			case 3:
				keys.right_shift = 0;
				break;
			case 4:
				keys.alt = 0;
				break;			
		}
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
		key = kbdus[scancode];
		switch (key)
		{
			case CTRL:
				keys.ctrl = 1;
				break;
			case LEFT_SHIFT:
				keys.left_shift = 1;
				break;
			case RIGHT_SHIFT:
				keys.right_shift = 1;
				break;
			case ALT:
				keys.alt = 1;
				break;
			case CAPS_LOCK:
				keys.capslock = !keys.capslock;
				break;
			case NUM_LOCK:
				keys.numlock = !keys.numlock;
				break;
			case SCROLL_LOCK:
				keys.scrolllock = !keys.scrolllock;
				break;
			default:
				if (keys.left_shift || keys.right_shift || keys.capslock)
				{
					key = kbdus[scancode+128];
				}
				shell_char(key);
				break;
				
		}
    }
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
