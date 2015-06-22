#include "memory.h"
#include "vga.h"
#include "string.h"
#include "isrs.h"
#include "pageframeallocator.h"


extern unsigned int endkernel;

void mem_init()
{
	// create page directory after the end of kernel
	unsigned int page_aligned_end = (endkernel & PAGE_ADDR) + 0x1000;
	mem_cur_page_dir = (unsigned int*)page_aligned_end;
	for(int i = 0; i < 1024; i++)
	{
	    mem_cur_page_dir[i] = PAGE_NOTHING;
	}
	// identity map the first 4 MB
	for (int i = 0; i < 1024; i++)
	{
		mem_map(i*4096, i*4096, PAGE_RW);
	}
	mem_set_page_dir(mem_cur_page_dir);
	//reads cr0, switches the "paging enable" bit, and writes it back.
	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
	// Now pagination is enabled the first 1024 pages of 4K (= 4M) are present in memory and identity-mapped
	isrs_install_handler(14, page_fault_handler);
}

void mem_set_page_dir(unsigned int * page_dir) 
{
	//moves mem_cur_page_dir (which is a pointer) into the cr3 register.
	asm volatile("mov %0, %%cr3":: "b"(page_dir));
}

void mem_map(unsigned int virtual_addr, unsigned int physical_addr, unsigned int flags)
{
	unsigned int pdir, page, *new_page_table;
	pdir = (virtual_addr >> 22); // 10 upper bits
	page = (virtual_addr >> 12) & 0x3FF; // 10 next bits

	new_page_table = mem_get_page_table(pdir);
	new_page_table[page] = (physical_addr & PAGE_ADDR) | PAGE_PRESENT | flags;
	if ((mem_cur_page_dir[pdir] & PAGE_PRESENT) == 0) // if page dir not present, create page dir
	{
		mem_cur_page_dir[pdir] = (unsigned int)new_page_table | PAGE_PRESENT | flags;
	}
}

// simple page fault handler that maps to first free page frame
void page_fault_handler(struct regs * r)
{
	unsigned int cr2;
	unsigned int frame = pageframe_alloc();
	if (frame == 0) {
		
	}
	// get fault address
	asm volatile("mov %%cr2, %0": "=b"(cr2));
	if ((r->err_code & 1) == 0) // page not present in memory
	{
		if ((r->err_code & 2) == 0) // read access
		{
			mem_map(cr2, frame, PAGE_NOTHING);
		}
		else // write access
		{
			mem_map(cr2, frame, PAGE_RW);
		}
	}
	else // page present -> protection fault
	{
		vga_puts("protection fault");
	}
}