#ifndef POOL_ALLOC_H
#define POOL_ALLOC_H

#include <types.h>
#include <debug.h>

#define CHUNK_SZ 64
typedef union Chunk Chunk;
union Chunk {
    Chunk *next;
    char arr[CHUNK_SZ];
};

typedef struct ArrayStart ArrayStart;
struct ArrayStart {
    Chunk *arr;
    ArrayStart *next;
};

typedef struct Pool Pool;
struct Pool {
    Chunk *free_chunk; // Available chunks of memory
    ArrayStart *array_starts;
};

Pool *pool_new(size);
void *pool_alloc(Pool *);
bool pool_expand(Pool *, size);
void pool_free(Pool *, void *);
void pool_close(Pool *);
#endif
