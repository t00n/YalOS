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

/*
#define MEM_BLK_SIZE 0x1000 // 4k
#define MEM_BLK_LIST MEM_BLK_SIZE*0x1000 // 4k blk = 16Mo
#define MEM_START 0x2000 // 8k blk = 32Mo
#define MEM_SIZE 0x100000 // 1M blk = 4Go

struct mem_blk // 16o
{
	void* ptr;
	bool free;
	struct mem_blk* next;
	uint32_t fill;
};

struct mem_blk* memory;

void mem_init();
void* malloc(size_t size);
void free(void* ptr);
*/

#endif
