#ifndef __MEMORY_H
#define __MEMORY_H

#include "system.h"


typedef struct page_dir_entry
{
	uint16_t first;
	uint8_t second;
	uint8_t flags;
} page_dir_entry;

typedef struct page_table_entry
{
	uint16_t first;
	uint8_t second;
	uint8_t flags;
} page_table_entry;

#endif
