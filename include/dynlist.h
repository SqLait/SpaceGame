#ifndef DYNLIST_H
#define DYNLIST_H

#include <stdlib.h>     // malloc
#include <string.h>     // memcpy

/* Structure of a dynlist:
 * size_t capacity
 * size_t length
 * size_t stride
 * void *memory
 */

enum {
    CAPACITY,
    LENGTH,
    STRIDE,
    dynlist_FIELDS
};

void *_dynlist_create(size_t length, size_t stride);
void _dynlist_destroy(void *arr);

size_t _dynlist_field_get(void *arr, size_t field);
void _dynlist_field_set(void *arr, size_t field, size_t value);

void *_dynlist_resize(void *arr);

void *_dynlist_push(void *arr, void *xptr);
void _dynlist_pop(void *arr, void *dest);
void _dynlist_remove(void *, int);

#define dynlist_DEFAULT_CAP 1
#define dynlist_RESIZE_FACTOR 2

#define dynlist_create(type) _dynlist_create(dynlist_DEFAULT_CAP, sizeof(type))
#define dynlist_create_prealloc(type, capacity) _dynlist_create(capacity, sizeof(type))
#define dynlist_destroy(arr) _dynlist_destroy(arr)
#define dynlist_remove(arr, index) _dynlist_remove(arr, index)

#define dynlist_push(arr, x) arr = _dynlist_push(arr, &x)
#define dynlist_push_rval(arr, x) \
    do { \
        __auto_type temp = x; \
        arr = _dynlist_push(arr, &temp); \
    } while (0)

#define dynlist_pop(arr, xptr) _dynlist_pop(arr, xptr)

#define dynlist_capacity(arr) _dynlist_field_get(arr, CAPACITY)
#define dynlist_length(arr) _dynlist_field_get(arr, LENGTH)
#define dynlist_stride(arr) _dynlist_field_get(arr, STRIDE)

#endif // dynlist
