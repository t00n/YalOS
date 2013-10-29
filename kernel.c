#include "gdt.h"
#include "term.h"

#if defined(__linux__)
#error "Not using cross-compiler"
#endif

void kernel_main()
{
	gdt_install();
	terminal_initialize();
	
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
