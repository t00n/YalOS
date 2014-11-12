#ifndef __MEMORY_H
#define __MEMORY_H

#include "system.h"

enum
{
	PDIR_NOTHING = 0,
	PDIR_PRESENT = 1,
	PDIR_RW = 2,
	PDIR_USER = 4,
	PDIR_WRITE = 8,
	PDIR_NOCACHE = 16,
	PDIR_ACCESS = 32,
	PDIR_SIZE = 128
};

enum 
{
	PG_NOTHING = 0,
	PG_PRESENT = 1,
	PG_RW = 2,
	PG_USER = 4,
	PG_WRITE = 8,
	PG_NOCACHE = 16,
	PG_ACCESS = 32,
	PG_DIRTY = 64,
	PG_GLOBAL = 256
};

void mem_init();


#endif
