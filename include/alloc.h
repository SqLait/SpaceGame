#ifndef ALLOC_H
#define ALLOC_H

#include <types.h>
#include <debug.h>
#include <stdio.h>

#define CHUNK_SZ 64
typedef struct Allocator Allocator;
typedef void *(*alloc_fn)(Allocator*, size);
typedef void (*free_fn)(Allocator*, void *);
typedef bool (*expand_fn)(Allocator*, size);
typedef void *(*realloc_fn)(Allocator*, size);
typedef void (*close_fn)(Allocator*);

struct Allocator {
    void *ctx; /*context pointer pointing to the allocator implementation*/
    alloc_fn alloc; /*Allocates data from the allocator implementation*/
    free_fn free; /*frees data from the allocator*/
    expand_fn expand; /*Add extra memory to the allocator (NEVER use both expand and realloc on the same allocator)*/
    realloc_fn realloc; /*Add extra memory from a function (NEVER use both expand and realloc on the same allocator)*/
    close_fn close; /*Closes (frees) the allocator rather than the data*/
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
Allocator pool_allocator(Pool *);
Allocator c_allocator(void);

Pool *pool_new(size);
void *pool_alloc(Pool *);
bool pool_expand(Pool *, size);
void pool_free(Pool *, void *);
void pool_close(Pool *);
#endif
