#ifndef __PAGEFRAMEALLOCATOR_H
#define __PAGEFRAMEALLOCATOR_H

#include <stdbool.h>

unsigned int pageframe_list[1024*32];

bool pageframe_isfree(unsigned int frame);

void pageframe_free(unsigned int frame);

void pageframe_unfree(unsigned int frame);

unsigned int pageframe_alloc();

#endif // __PAGEFRAMEALLOCATOR_H