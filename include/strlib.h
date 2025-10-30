#ifndef STRLIB_H
#define STRLIB_H

#include <stddef.h>

#define STR_INIT_CAPACITY 16

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} dstring_t;

#endif
