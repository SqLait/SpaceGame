#include "alloc.h"
#include "debug.h"
#include "types.h"

Pool *pool_new(size pool_sz) {
    Pool* pool = malloc(sizeof(Pool));
    if (pool == NULL)
        return NULL;

    Chunk *arr = pool->free_chunk = malloc(pool_sz * sizeof(Chunk));
    if (arr == NULL) {
        free(pool);
        return NULL;
    }

    for (size i = 0; i < pool_sz - 1; i++)
        arr[i].next = &arr[i + 1];
    arr[pool_sz - 1].next = NULL;

    pool->array_starts = malloc(sizeof(ArrayStart));
    if (pool->array_starts == NULL) {
        free(arr);
        free(pool);
        return NULL;
    }

    pool->array_starts->next = NULL;
    pool->array_starts->arr = arr;

    return pool;
}

void *pool_alloc(Pool *pool) {
    if (pool == NULL || pool->free_chunk == NULL)
        return NULL;

    Chunk *result = pool->free_chunk;
    pool->free_chunk = pool->free_chunk->next;
    return result;
}

bool pool_expand(Pool *pool, size extra) {
    if (pool == NULL || extra == 0)
        return false;

    Chunk *extra_arr = malloc(extra * sizeof(Chunk));
    if (extra_arr == NULL)
        return false;

    for (size i = 0; i < extra - 1; i++)
        extra_arr[i].next = &extra_arr[i + 1];

    extra_arr[extra - 1].next = pool->free_chunk;
    pool->free_chunk = extra_arr;

    ArrayStart *array_start = malloc(sizeof(ArrayStart));
    if (array_start == NULL) {
        free(extra_arr);
        return false;
    }

    array_start->arr = extra_arr;
    array_start->next = pool->array_starts;
    pool->array_starts = array_start;

    return true;
}

void pool_free(Pool *pool, void *ptr) {
    if (pool == NULL || ptr == NULL)
        return;

    Chunk *freed = ptr;
    freed->next = pool->free_chunk;
    pool->free_chunk = freed;
}

void pool_close(Pool* pool) {
    if (pool == NULL)
        return;
    ArrayStart *array_start = pool->array_starts;
    while (array_start != NULL) {
        ArrayStart *next = array_start->next;
        free(array_start->arr);
        free(array_start);
        array_start = next;
    }
    free(pool);
}


/*================c_alloc================*/
//
static void *_c_allocator_alloc(Allocator *a, size n) {
    (void)a;
    return malloc(n);
}

static void _c_allocator_free(Allocator *a, void *p) {
    (void)a;
    free(p);
}

static void *_c_allocator_realloc(Allocator *a, size n) {
    return realloc(a->ctx, n);
}

/*================pool_alloc================*/
//
static void *_pool_allocator_alloc(Allocator *a, size n) {
    (void)n;
    return pool_alloc((Pool *)a->ctx);
}

static void _pool_allocator_free(Allocator *a, void *ptr) {
    pool_free((Pool *)a->ctx, ptr);
}

static bool _pool_allocator_expand(Allocator *a, size n) {
    return pool_expand((Pool *)a->ctx, n);
}

static void _pool_alloc_close(Allocator *a) {
    pool_close((Pool *)a->ctx);
}
/*================noop_alloc================*/
//
static void *_noop_allocator_alloc(Allocator *a, size n) {
    (void)a;
    (void)n;
    DEBUG_LOG("No valid allocator found on this Allocator", a);
    return NULL;
}

static void _noop_allocator_free(Allocator *a, void *ptr) {
    (void)a;
    (void)ptr;
    DEBUG_LOG("No valid allocator found on this Allocator", a);
}

static bool _noop_allocator_expand(Allocator *a, size n) {
    (void)a;
    (void)n;
    DEBUG_LOG("No valid allocator found on this Allocator", a);
    return NULL;
}

static void _noop_alloc_close(Allocator *a) {
    (void)a;
    DEBUG_LOG("No valid allocator found on this Allocator", a);
}

static void *_noop_allocator_realloc(Allocator *a, size n) {
    (void)a;
    (void)n;
    DEBUG_LOG("No valid allocator found on this Allocator", a);
    return NULL;
}

Allocator c_allocator(void) {
    return (Allocator) {
        .ctx = NULL,
        .free = _c_allocator_free,
        .alloc = _c_allocator_alloc,
        .realloc = _c_allocator_realloc,
        .expand = _noop_allocator_expand,
        .close = _noop_alloc_close,
    };
}

Allocator pool_allocator(Pool *pool) {
    return (Allocator) {
        .ctx = pool,
        .alloc = _pool_allocator_alloc,
        .realloc = _noop_allocator_realloc,
        .free = _pool_allocator_free,
        .expand = _pool_allocator_expand,
        .close = _pool_alloc_close,
    };
}
