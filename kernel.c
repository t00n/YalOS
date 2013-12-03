#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "term.h"
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
	__asm__ __volatile__ ("sti"); 
	term_init();
	shell_init();
	mem_init();
	
	char** test = strsplit("haha hehe hihi hoho       \0", ' ');
	for (int i = 0; i < strlen(*test); ++i)
	{
		term_puts(test[i]);
		term_putc('\n');
	}
	
	shell_loop();	
}
