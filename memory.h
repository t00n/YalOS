#ifndef __MEMORY_H
#define __MEMORY_H

#include "system.h"

#define START_OF_MEMORY 0xFFFFFF // 16-256-4096-64k-1Mo-16Mo
#define SIZE_OF_MEMORY 0xFFFFFF // 16-256-4096-64k-1Mo-16Mo

struct mem_blk
{
	void* ptr;
	size_t size;
	bool free;
	struct mem_blk* next;
};

struct mem_blk* memory;

void mem_init();
void* malloc(size_t size);

#endif
