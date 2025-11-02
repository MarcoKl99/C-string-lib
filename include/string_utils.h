#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>
#include "dtypes.h"

///////////////////////////////////////
// Utility functions based on char * //
///////////////////////////////////////
size_t str_length(const char *str);
int str_equal(const char *s1, const char *s2);
char *str_copy(const char *src, char *dest);
char *str_find(char *haystack, char *needle);
size_t str_count(const char *s, const char *substr);
char **str_split(const char *s, char delimiter, size_t *count);

#endif
