/**
 * author:nejidev
 * date:2019-12-05
 */
#ifndef __SRAM_H
#define __SRAM_H

#include <stdio.h>

#define SRAM_POOLS_CHUNK_SIZE (256)
#define SRAM_POOLS_HEAP_SIZE  (4*1024)														    

typedef struct sram_mem_chunk {
	void  *alloc;
	size_t alloc_size;
	size_t chunk_size;
	size_t current;
	size_t cleanup; //0 cleanup 1 alloc
	struct sram_mem_chunk *next;
} sram_mem_chunk;

void *sram_malloc(size_t size);
void sram_free(void *ptr);
void sram_pools_dump();

#endif
