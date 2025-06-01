#include "dynlist.h"
#include "types.h"
#include "debug.h"

/*

Dynamic Array

A dynlist has three hidden fields of type `size` stored in it's header:
    - capacity: size in `stride`-sized units of the allocated buffer.
    - length: the number of `stride`-sized units currently filled.
    - stride: the sizeof the datatype being stored in the dynlist.

To get the ith element in the array, you can use bracket notation (`arr[i]`),
or the `dynlist_get` method which does bounds checking.

To set the ith element of the array, use either bracket notation
(`arr[i] = x;`), or the `dynlist_set` method which does bounds checking.
*/

// Returns a pointer to the start of a new dynlist (after the header) which
// has `init_cap` units of `stride` bytes.
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

void _dynlist_remove(void *arr, int index) {
    size len = dynlist_length(arr);
    if (index > len - 1 || index < 0) {
        printf("dynlist operation canceled: trying to access outside the array");
        return;
    }

    void *item = &arr[index];
    // set the item on the index to NULL
    // Remove the entry out of the list
    for (int i = index; i < len; i++) {
        // remove the entry specified
        // Loop over the list to change the pointers to the new order
    }
    
    // Set the size to size - 1
}
