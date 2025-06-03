#ifndef DYNLIST_H
#define DYNLIST_H

#include <stdlib.h>     // malloc
#include <string.h>     // memcpy
#include "types.h"
#include "debug.h"

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

void *_dynlist_create(size, size);
void _dynlist_destroy(void *);

size _dynlist_field_get(void *, size);
void _dynlist_field_set(void *, size, size);

void *_dynlist_resize(void *);

void *_dynlist_push(void *, void *);
void _dynlist_pop(void *, void *);
void _dynlist_remove(void *, void *);
void _dynlist_removeat(void *, int);

#define dynlist_DEFAULT_CAP 1
#define dynlist_RESIZE_FACTOR 2

#define dynlist_init(type) _dynlist_create(dynlist_DEFAULT_CAP, sizeof(type))
#define dynlist_create_prealloc(type, capacity) _dynlist_create(capacity, sizeof(type))
#define dynlist_destroy(arr) _dynlist_destroy(arr)
#define dynlist_removeat(arr, index) _dynlist_removeat(arr, index)
#define dynlist_remove(arr, ptr) _dynlist_remove(arr, ptr)

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


void *_dynlist_create(size init_cap, size stride) {
    size header_size = dynlist_FIELDS * sizeof(size);
    size arr_size = init_cap * stride;
    size *arr = (size *) malloc(header_size + arr_size);
    arr[CAPACITY] = init_cap;
    arr[LENGTH] = 0;
    arr[STRIDE] = stride;
    return (void *) (arr + dynlist_FIELDS);
}

void _dynlist_destroy(void *arr) {
    free(arr - dynlist_FIELDS * sizeof(size));
}

// Returns the dynlist's field which is specified by passing
// one of CAPACITY, LENGTH, STRIDE.
size _dynlist_field_get(void *arr, size field) {
    return ((size *)(arr) - dynlist_FIELDS)[field];
}

void _dynlist_field_set(void *arr, size field, size value) {
    ((size *)(arr) - dynlist_FIELDS)[field] = value;
}

// Allocates a new dynlist with twice the size of the one passed in, and retaining
// the values that the original stored.
void *_dynlist_resize(void *arr) {
    void *temp = _dynlist_create( // Allocate new dynlist w/ more space.
        dynlist_RESIZE_FACTOR * dynlist_capacity(arr),
        dynlist_stride(arr)
    );
    memcpy(temp, arr, dynlist_length(arr) * dynlist_stride(arr)); // Copy erythin' over.
    _dynlist_field_set(temp, LENGTH, dynlist_length(arr)); // Set `length` field.
    _dynlist_destroy(arr); // Free previous array.
    return temp;
}

void *_dynlist_push(void *arr, void *xptr) {
    if (dynlist_length(arr) >= dynlist_capacity(arr))
        arr = _dynlist_resize(arr);

    memcpy(arr + dynlist_length(arr) * dynlist_stride(arr), xptr, dynlist_stride(arr));
    _dynlist_field_set(arr, LENGTH, dynlist_length(arr) + 1);
    return arr;
}

// Removes the last element in the array, but copies it to `*dest` first.
void _dynlist_pop(void *arr, void *dest) {
    memcpy(dest, arr + (dynlist_length(arr) - 1) * dynlist_stride(arr), dynlist_stride(arr));
    _dynlist_field_set(arr, LENGTH, dynlist_length(arr) - 1); // Decrement length.
}

void _dynlist_removeat(void *arr, int index) {
    size len = dynlist_length(arr);
    size stride = dynlist_stride(arr);

    ASSERT_MSG(index >= 0 && index < len,
               "dynlist operation canceled: index out of bounds");

    if (index == len - 1) {
        char *elem_ptr = (char *)arr + index * stride;
        dynlist_pop(arr, elem_ptr);
        return;
    }

    char *base = (char *)arr;
    char *target = base + index * stride;
    char *next = target + stride;

    // Move the memory block left by one element
    memmove(target, next, (len - index - 1) * stride);

    // Decrease the length
    _dynlist_field_set(arr, LENGTH, len - 1);
}

/*Clears all the elements in the dynlist*/
void _dynlist_clear(void *arr) {
    size len = dynlist_length(arr);
    for (int i = 0; i < len; i++) {
        // remove all items from the list.
    }
    _dynlist_field_set(arr, LENGTH, 0);
}

/*Works for simple types (int float char) but not for structs and unions*/
void dynlist_search(void *arr, size elem_size, void *ptr) {
    size len = dynlist_length(arr);
    char *base = (char *)arr;
    for (size i = 0; i < len; i++) {
        if (memcmp(base + i * elem_size, ptr, elem_size) == 0) {
            printf("ITEM FOUND!\n");
            break;
        }
    }
}
#endif // dynlist
