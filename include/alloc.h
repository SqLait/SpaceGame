#ifndef ALLOC_H
#define ALLOC_H
#include "types.h"
#define POOL_SIZE 1024
typedef struct Block {
    struct Block *next;
} Block;

typedef struct {
    Block *freeList;
    size block_size;
    byte pool[POOL_SIZE];
} MemoryPool;

void init_pool(MemoryPool *, size);
void *pool_alloc(MemoryPool *);
void pool_free(MemoryPool *, void *);
void pool_clear(MemoryPool *);
#endif
