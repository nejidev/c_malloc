/**
 * author:nejidev
 * date:2019-12-05
 */
#include "sram.h"

//static stack or physics memory address
static char mem[SRAM_POOLS_HEAP_SIZE] = {0};
static sram_mem_chunk *pools_mem_head = NULL;

static sram_mem_chunk *sram_pools_init()
{
    int  i;
    int  chunk_total;
    char *base_alloc;

    if ( ! pools_mem_head ) {
        chunk_total = SRAM_POOLS_HEAP_SIZE / ( sizeof(sram_mem_chunk) +
                                                SRAM_POOLS_CHUNK_SIZE );
        base_alloc = mem + chunk_total * sizeof(sram_mem_chunk);
        pools_mem_head = (sram_mem_chunk *)mem;

        for ( i = 0; i < chunk_total; i++ ) {
            pools_mem_head[i].alloc      = (void *)(base_alloc +
                                                i * SRAM_POOLS_CHUNK_SIZE);
            pools_mem_head[i].current    = i;
            pools_mem_head[i].alloc_size = 0;
            pools_mem_head[i].chunk_size = SRAM_POOLS_CHUNK_SIZE;
            pools_mem_head[i].cleanup    = 0;
            pools_mem_head[i].next       = ((i + 1) < chunk_total) ?
                                                &pools_mem_head[i + 1] : NULL;
        }
    }
    return pools_mem_head;
}

void *sram_malloc(size_t size)
{
    void *ptr = NULL;
    size_t alloc_size = 0;
    sram_mem_chunk *mem_head    = sram_pools_init();
    sram_mem_chunk *mem_alloc   = NULL;
    sram_mem_chunk *mem_cleanup = NULL;

    while ( mem_head ) {
        if ( 0 == mem_head->cleanup ) {
            mem_alloc  = mem_head;
            alloc_size = 0;
            ptr = mem_alloc->alloc;
            while ( mem_alloc ) {
                if ( 0 == alloc_size ) {
                    mem_alloc->alloc_size = size;
                }
                mem_alloc->cleanup = 1;
                alloc_size += mem_alloc->chunk_size;
                if ( alloc_size > size ) {
                    break ;
                }
                mem_alloc = mem_alloc->next;
            }
            //alloc success
            if ( alloc_size >= size ) {
                break ;
            }
            //alloc failed cleanup
            else {
                ptr = NULL;
                mem_cleanup = mem_head;
                while ( mem_cleanup && mem_cleanup != mem_alloc ) {
                    mem_cleanup->alloc_size = 0;
                    mem_cleanup->cleanup    = 0;
                    mem_cleanup = mem_cleanup->next;
                }
            }
        }

        mem_head = mem_head->next;
    }

    return ptr;
}

void sram_free(void *ptr)
{
    int free_size;
    sram_mem_chunk *mem_head = sram_pools_init();

    if ( ! ptr ) return ;

    while ( mem_head ) {
        if ( mem_head->alloc == ptr && 0 < mem_head->cleanup ) {
            free_size = mem_head->alloc_size;
            while ( 0 < free_size ) {
                free_size -= mem_head->chunk_size;
                mem_head->alloc_size = 0;
                mem_head->cleanup = 0;
                mem_head = mem_head->next;
            }
            return ;
        }

        mem_head = mem_head->next;
    }
}

void sram_pools_dump()
{
    sram_mem_chunk *mem_head = sram_pools_init();

    while ( mem_head ) {
        printf("current:%ld alloc_size:%ld cleanup:%ld \n", mem_head->current,
                    mem_head->alloc_size, mem_head->cleanup);

        mem_head = mem_head->next;
    }
}
