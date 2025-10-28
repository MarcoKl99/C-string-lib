#ifndef STR_SPLIT_TEST_DATA_H
#define STR_SPLIT_TEST_DATA_H

#include <stdlib.h>

typedef struct {
    const char *s;
    char delimiter;
    size_t num_tokens;
    const char **tokens;
} StrSplitTestData;

#endif
