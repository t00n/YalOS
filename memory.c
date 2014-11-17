#include "memory.h"

extern unsigned int endkernel;

void mem_init()
{
	int i = 0, address = 0;
	unsigned int cr0;
	// create page directory after the end of kernel
	unsigned int page_aligned_end = (endkernel & 0xFFFFF000) + 0x1000;
	page_directory = (unsigned int*)page_aligned_end;
	for(i = 0; i < 1024; i++)
	{
	    //attribute: supervisor level, read/write, not present.
	    page_directory[i] = PDIR_NOTHING;
	}
	// create the first page table after the page directory
	page_tables[0] = page_directory + 1024;
	for (i = 0; i < 1024; i++)
	{
		page_tables[0][i] = address | PG_RW | PG_PRESENT;
		address += 4096;
	}
	// assign a page table and make it present in memory
	page_directory[0] = (unsigned int)page_tables[0];
	page_directory[0] |= PDIR_RW | PDIR_PRESENT;
	//moves page_directory (which is a pointer) into the cr3 register.
	asm volatile("mov %0, %%cr3":: "b"(page_directory));
	//reads cr0, switches the "paging enable" bit, and writes it back.
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
	// Now pagination is enabled the first 1024 pages of 4K (= 4M) are present in memory and identity-mapped
	isrs_install_handler(14, &page_fault_handler);
}

void page_fault_handler(struct regs * r)
{

}