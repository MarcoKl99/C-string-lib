#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>

size_t str_length(const char *str);
char *str_copy(const char *src, char *dest);
size_t str_concat(const char *s1, const char *s2, char *buf, size_t buf_size);
int str_equal(const char *s1, const char *s2);
const char *str_find(const char *haystack, const char *needle);

#endif
