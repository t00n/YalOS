#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "vga.h"
#include "kb.h"
#include "timer.h"
#include "shell.h"
#include "memory.h"
#include "string.h"

#if defined(__linux__)
#error "Not using cross-compiler"
#endif

void kernel_main()
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	keyboard_install();
	timer_install();
	mem_init();
	vga_init();
	unsigned int * test = 0x500000;
	*test = 'a';
	vga_puts(0x500000);
}
