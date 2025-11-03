#ifndef DTYPES_H
#define DTYPES_H

#include <stdlib.h>

// Some constants
#define MAX_PAIRS 100
#define STR_INIT_CAPACITY 16
#define MAX_CLI_ARG_LENGTH 512

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

typedef struct
{
    char *s1;
    char *s2;
    char *s3;
    char *s4;
} StringQuad;

typedef struct
{
    char *original;
    char *s_insert;
    size_t insert_after_idx;
    char *result;
} StrInsertTestData;

typedef struct
{
    dstring_t *s;
    char **keys;
    char **values;
    size_t num_params;
    char *result;
} DstringTemplateTestData;

typedef struct
{
    char **keys;
    char **values;
    size_t count;
} env_t;

typedef struct
{
    char template_path[MAX_CLI_ARG_LENGTH];
    char env_path[MAX_CLI_ARG_LENGTH];
    char output_path[MAX_CLI_ARG_LENGTH];
} cli_args_t;

#endif
