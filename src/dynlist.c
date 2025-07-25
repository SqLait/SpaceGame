#include "dynlist.h"

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
    free((char *)arr - dynlist_FIELDS * sizeof(size));
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

    char *dst = (char *)arr + dynlist_length(arr) * dynlist_stride(arr);
    memcpy(dst, xptr, dynlist_stride(arr));
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

void _dynlist_remove(void *arr, void *ptr) {
    size len = dynlist_length(arr);
    size stride = dynlist_stride(arr);
    char *base = (char *)arr;

    for (size i = 0; i < len; i++) {
        char *current = base + i * stride;
        if (current == (char *)ptr) {
            _dynlist_removeat(arr, i);
            return;
        }
    }

    printf("dynlist_remove: pointer not found in list range\n");
}

/*Clears all the elements in the dynlist*/
void _dynlist_clear(void *arr) {
    size len = dynlist_length(arr);
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
