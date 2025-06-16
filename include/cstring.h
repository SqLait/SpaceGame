#ifndef CSTRING_H
#define CSTRING_H
#include "types.h"
typedef struct {
    char *str;
    u32 size;
} string;

string cstr_create(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        
    }
}
#endif
