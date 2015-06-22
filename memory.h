#ifndef __MEMORY_H
#define __MEMORY_H

struct regs;

enum 
{
	PAGE_PRESENT = 1,
	PAGE_RW = 2,
	PAGE_USER = 4,
	PAGE_WRITE = 8,
	PAGE_NOCACHE = 16,
	PAGE_ACCESS = 32,
	PAGE_DIRTY = 64,
	PAGE_SIZE = 128,
	PAGE_GLOBAL = 256,
	PAGE_ADDR = 0xFFFFF000,
	PAGE_NOTHING = 0
};

unsigned int * page_directory;

unsigned int * getPageTable(unsigned int pdir);

void mem_init();

void map_page(unsigned int virtual_addr, unsigned int physical_addr, unsigned int flags);

void page_fault_handler(struct regs * r);

unsigned int get_free_page_frame();

#endif
