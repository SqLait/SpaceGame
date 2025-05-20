#include "alloc.h"
#include <assert.h>

void init_memorypool(MemoryPool *pool) {
    pool->freeList = (Block *)pool->pool;
    Block *current = pool->freeList;

    for (int i = 0; i < (POOL_SIZE / sizeof(Block)) - 1; i++) {
        current->next = (Block *)((unsigned char *)current + sizeof(Block));
        current = current->next;
    }

    current->next = NULL;
}

void *pool_alloc(MemoryPool *pool) {
    assert(pool->freeList == NULL);

    Block *block = pool->freeList;
    pool->freeList = block->next;

    return (void *)block;
}

void pool_free(MemoryPool *pool, void *ptr) {
    Block *block = (Block *)ptr;
    block->next = pool->freeList;
    pool->freeList = block;
}
