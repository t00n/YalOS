#ifndef __MEMORY_H
#define __MEMORY_H

struct regs;

enum 
{
	PAGE_NOTHING = 0,
	PAGE_PRESENT = 1,
	PAGE_RW = 2,
	PAGE_USER = 4,
	PAGE_WRITE = 8,
	PAGE_NOCACHE = 16,
	PAGE_ACCESS = 32,
	PAGE_DIRTY = 64,
	PAGE_SIZE = 128,
	PAGE_GLOBAL = 256,
	PAGE_ADDR = 0xFFFFF000
};

unsigned int * mem_cur_page_dir;

unsigned int * mem_get_page_table(unsigned int pdir);

void mem_init();

void mem_set_page_dir(unsigned int *);

void mem_map(unsigned int virtual_addr, unsigned int physical_addr, unsigned int flags);

void page_fault_handler(struct regs * r);

#endif
