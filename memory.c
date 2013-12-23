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
		next->size = START_OF_MEMORY+SIZE_OF_MEMORY-(int)next->ptr;
		next->free = true;
		return mem->ptr;
	}
	return 0;
}

/*TO DO
 * mem_blk -> mem_ptr
 * mem_blk -> 4Ko ~ page frame
 * void mem_init()
{
	memory = (struct mem_blk*)MEM_BLK_LIST;
	memory->free = true;
	memory->next = NULL;
	memory->ptr = (struct mem_blk*)MEM_START;
}

void* malloc(size_t size) // = brk(void*)
{
	struct mem_blk* mem = memory;
	while (mem->free = false && mem->next != NULL)
	{
		mem = mem->next;
	}
	if (mem->next == NULL)
	{
		if (mem->ptr + MEM_BLK_SIZE == MEM_SIZE)
		{
			return 0; // no place anymore
		}
		struct mem_blk* next = mem+1;
		next->next = NULL;
		next->ptr = mem->ptr+MEM_BLK_SIZE;
		next->free = true;
		mem->next = next;
		mem = next;
	}
	if (mem->free == true)
	{
		mem->free = false;
		return mem->ptr;
	}
}
void free(void* ptr)
{
	
}
 
*/
