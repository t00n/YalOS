#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "term.h"
#include "kb.h"

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
	__asm__ __volatile__ ("sti"); 
	terminal_initialize();
	
	while(true) {}
	
	//~ terminal_putchar(2/0);
	
	
	//~ int i = 2/0;
	//~ terminal_putchar(i);
	
	//~ terminal_writestring("Hello, kernel world\n");
	//~ 
	//~ while (1)
	//~ {
		//~ int i = 2/0;
	//~ }
	
	//~ for (char c = 48; c < 73; ++c)
	//~ {
		//~ terminal_putchar(c);
		//~ terminal_putchar('\n');
	//~ }
	//~ terminal_writestring("Hello, kernel world\n");
	//~ terminal_writestring("haha\b\t\rbaba");
}
