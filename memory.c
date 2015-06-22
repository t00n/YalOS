#include "memory.h"
#include "vga.h"
#include "string.h"
#include "isrs.h"


extern unsigned int endkernel;

void mem_init()
{
	int i = 0, address = 0;
	unsigned int cr0;
	// create page directory after the end of kernel
	unsigned int page_aligned_end = (endkernel & PAGE_ADDR) + 0x1000;
	page_directory = (unsigned int*)page_aligned_end;
	for(i = 0; i < 1024; i++)
	{
	    page_directory[i] = PAGE_NOTHING;
	}
	// create the first page table after the page directory
	unsigned int * first_page_table = getPageTable(0);
	for (i = 0; i < 1024; i++)
	{
		first_page_table[i] = address | PAGE_RW | PAGE_PRESENT;
		address += 4096;
	}
	// assign a page table and make it present in memory
	page_directory[0] = (unsigned int)first_page_table | PAGE_RW | PAGE_PRESENT;
	//moves page_directory (which is a pointer) into the cr3 register.
	asm volatile("mov %0, %%cr3":: "b"(page_directory));
	//reads cr0, switches the "paging enable" bit, and writes it back.
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
	// Now pagination is enabled the first 1024 pages of 4K (= 4M) are present in memory and identity-mapped
	isrs_install_handler(14, page_fault_handler);
}

unsigned int * getPageTable(unsigned int pdir)
{
	return page_directory + 1024 * (pdir+1);
}

void map_page(unsigned int virtual_addr, unsigned int physical_addr, unsigned int flags)
{
	unsigned int pdir, page, *new_page_table;
	pdir = (virtual_addr >> 22); // 10 upper bits
	page = (virtual_addr >> 12) & 0x3FF; // 10 next bits

	new_page_table = getPageTable(pdir);
	new_page_table[page] = (physical_addr & PAGE_ADDR) | PAGE_PRESENT | flags;
	if ((page_directory[pdir] & PAGE_PRESENT) == 0) // if page dir not present, create page dir
	{
		page_directory[pdir] = (unsigned int)new_page_table | PAGE_PRESENT | flags;
	}
}

// simple page fault handler that maps to first free page frame
void page_fault_handler(struct regs * r)
{
	unsigned int cr2;
	unsigned int frame = get_free_page_frame();
	// get fault address
	asm volatile("mov %%cr2, %0": "=b"(cr2));
	if ((r->err_code & 1) == 0) // page not present in memory
	{
		if ((r->err_code & 2) == 0) // read access
		{
			map_page(cr2, frame, PAGE_NOTHING);
		}
		else // write access
		{
			map_page(cr2, frame, PAGE_RW);
		}
	}
	else // page present -> protection fault
	{
		vga_puts("protection fault");
	}
}

unsigned int get_free_page_frame()
{
	for (int i = 0; i < 1024; ++i) {
		unsigned int * page_dir = getPageTable(i);
		for (int j = 0; j < 1024; ++j) {
			unsigned int page = *(page_dir + j);
			if ( !(page & PAGE_PRESENT)) {
				return (page & PAGE_ADDR) >> 10;
			}
		}
	}
	// if we arrive here there is no free page frame
}