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
const char *str_find(const char *haystack, const char *needle);
size_t str_count(const char *s, const char *substr);
char **str_split(const char *s, char delimiter, size_t *count);

//////////////////////////////////
// Functions based on dstring_t //
//////////////////////////////////
dstring_t *dstring_init(const char *init_text);
void dstring_free(dstring_t *s);
void dstring_append(dstring_t *s, const char *suffix);
void dstring_reverse(dstring_t *str);
void dstring_to_upper(dstring_t *s);
void dstring_trim(dstring_t *s);

#endif
