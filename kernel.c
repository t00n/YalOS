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
	unsigned int * test = 0x400000;
	unsigned int value = *test;
	vga_putc(*test);
	*test = 'a';
	vga_putc(*test);
	unsigned int pdir = (0x400000 >> 22);
	unsigned int page = (0x400000 >> 12) & 0x3FF;
	unsigned int address = (page_directory+1024*(pdir+1))[page];

	asm volatile("mov %0, %%eax":: "b"(address));
	// vga_puts(0x500000);
}
