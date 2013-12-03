#include "memory.h"

void mem_init()
{
	memory = (struct mem_blk*)0x3FFFFF; // 4Mo
	memory->free = true;
	memory->next = NULL;
	memory->ptr = (struct mem_blk*)START_OF_MEMORY;
	memory->size = SIZE_OF_MEMORY;
}

void* malloc(size_t size)
{
	struct mem_blk* mem = memory;
	while (mem->next != NULL)
	{
		mem = mem->next;
	} // found last block
	if (mem->free == true && mem->size >= size)
	{
		struct mem_blk* next = mem+1;;
		mem->free = false;
		mem->size = size;
		mem->next = next;
		next->next = NULL;
		next->ptr = mem->ptr+mem->size;
		next->size = START_OF_MEMORY+SIZE_OF_MEMORY-(int)mem->ptr;
		next->free = true;
		return mem->ptr;
	}
	return 0;
}
