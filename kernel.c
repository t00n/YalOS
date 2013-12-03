#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "term.h"
#include "kb.h"
#include "timer.h"
#include "shell.h"
#include "memory.h"

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
	
	//~ char test[10] = "haha hhehe hihi hoho ";
	//~ char retest[10][10] = strsplit(test, ' ');
	//~ for (int i = 0; i < 6; ++i)
	//~ {
		//~ term_puts(retest[i]);
	//~ }
	char* test = malloc(5);
	test[0]='0';
	test[1]='1';
	test[2]='2';
	test[3]='3';
	test[4]='4';
	term_putc(test);
		
	shell_loop();	
}
