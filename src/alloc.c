#include "alloc.h"
#include "debug.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_pool(MemoryPool *pool, size block_size) {
    pool->block_size = (block_size < sizeof(Block *)) ? sizeof(Block *) : block_size;
    pool->freeList = (Block *)pool->pool;

    size num_blocks = POOL_SIZE / pool->block_size;
    Block *current = pool->freeList;

    for (size i = 0; i < num_blocks - 1; i++) {
        current->next = (Block *)((byte *)current + pool->block_size);
        current = current->next;
    }

    current->next = NULL;
}

void *pool_alloc(MemoryPool *pool) {
    ASSERT_MSG(pool->freeList != NULL, "ERROR: Pool exhaust");

    Block *block = pool->freeList;
    pool->freeList = block->next;

    return (void *)block;
}

void pool_free(MemoryPool *pool, void *ptr) {
    Block *block = (Block *)ptr;
    block->next = pool->freeList;
    pool->freeList = block;
}

void pool_clear(MemoryPool *pool) {
    pool->freeList = (Block *)pool->pool;
    size_t num_blocks = POOL_SIZE / pool->block_size;
    Block *current = pool->freeList;

    for (size_t i = 0; i < num_blocks - 1; i++) {
        current->next = (Block *)((byte *)current + pool->block_size);
        current = current->next;
    }

    current->next = NULL;
}
