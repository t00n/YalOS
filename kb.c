#include "kb.h"

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    1,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'y', '`',   2,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   3,				/* Right shift */
  '*',
    4,	/* Alt */
  ' ',	/* Space bar */
    5,	/* Caps lock */
    65,	/* 59 - F1 key ... > */
    66,   67,   68,   69,   70,   71,   72,   73,
    74,	/* < ... F10 */
    6,	/* 69 - Num lock*/
    7,	/* Scroll Lock */
    77,	/* Home key */
    83,	/* Up Arrow */
    78,	/* Page Up */
  '-',
    84,	/* Left Arrow */
    0,
    85,	/* Right Arrow */
  '+',
    79,	/* 79 - End key*/
    86,	/* Down Arrow */
    80,	/* Page Down */
    81,	/* Insert Key */
    82,	/* Delete Key */
    0,   0,   0,
    75,	/* F11 Key */
    76,	/* F12 Key */
    0,	/* All other keys are undefined */
};


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
		
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        terminal_putchar(kbdus[scancode]);
    }
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
