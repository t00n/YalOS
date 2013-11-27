#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "term.h"
#include "kb.h"
#include "timer.h"
#include "shell.h"

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
	shell_initialize();
	
	
	shell_loop();
	
	//~ while(true) {}
	
	//~ term_putc(2/0);
	
	
	//~ int i = 2/0;
	//~ term_putc(i);
	
	//~ term_puts("Hello, kernel world\n");
	//~ 
	//~ while (1)
	//~ {
		//~ int i = 2/0;
	//~ }
	
	//~ for (char c = 48; c < 73; ++c)
	//~ {
		//~ term_putc(c);
		//~ term_putc('\n');
	//~ }
	//~ term_puts("Hello, kernel world\n");
	//~ term_puts("haha\b\t\rbaba");
}
