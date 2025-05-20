#ifndef ALLOC_H
#define ALLOC_H
#include "types.h"
#define POOL_SIZE 1024
typedef struct Block {
    struct Block *next;
} Block;

typedef struct {
    Block *freeList;
    byte pool[POOL_SIZE];
} MemoryPool;

void init_memorypool(MemoryPool *);
void *pool_alloc(MemoryPool *);
void pool_free(MemoryPool *, void *);
#endif
