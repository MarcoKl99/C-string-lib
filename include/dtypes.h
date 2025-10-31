#ifndef DTYPES_H
#define DTYPES_H

#include <stdlib.h>

// Some constants
#define MAX_PAIRS 100
#define STR_INIT_CAPACITY 16

// The infamous dstring_t
typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} dstring_t;

// And a few more helpful colleagues here...
typedef struct
{
    const char *key;
    int value;
} Pair;

typedef struct
{
    const char *s;
    const char *substr;
    size_t count;
} StrCountTestData;

typedef struct
{
    const char *s;
    char delimiter;
    size_t num_tokens;
    const char **tokens;
} StrSplitTestData;

typedef struct
{
    char *s1;
    char *s2;
} StringTuple;

typedef struct
{
    char *s1;
    char *s2;
    char *s3;
} StringTriple;

#endif
