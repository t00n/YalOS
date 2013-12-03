#include "memory.h"

void mem_init()
{
	memory.free = true;
	memory.next = NULL;
	memory.ptr = START_OF_MEMORY;
	memory.size = SIZE_OF_MEMORY;
}

void* malloc(size_t size)
{
	struct mem_blk* mem = &memory;
	while (mem->next != NULL && (mem->free == false || mem->size < size))
	{
		mem = mem->next;
	} // found block or end of memory
	if (mem->free == true && mem->size >= size)
	{
		mem->free = false;
		mem->size = size;
		return mem->ptr;
	}
	return 0;
}
