#ifndef ALLOC_H
#define ALLOC_H

#include <types.h>
#include <debug.h>
#include <stdio.h>

#define CHUNK_SZ 64
typedef struct Allocator Allocator;
typedef void *(*alloc_fn)(Allocator*, size n);
typedef void (*free_fn)(Allocator*, void *p);

struct Allocator {
    alloc_fn malloc;
    free_fn free;
};

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
