#include "gdt.h"
#include "idt.h"
#include "term.h"

#if defined(__linux__)
#error "Not using cross-compiler"
#endif

void kernel_main()
{
	gdt_install();
	idt_install();
	//~ terminal_initialize();
	//~ 
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
	//~ char *ptr = 0;
	//~ terminal_putchar(*ptr);
}
