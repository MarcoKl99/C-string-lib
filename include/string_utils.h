#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>
#include "strlib.h"

///////////////////////////////////////
// Utility functions based on char * //
///////////////////////////////////////
size_t str_length(const char *str);
int str_equal(const char *s1, const char *s2);
char *str_copy(const char *src, char *dest);

//////////////////////////////////
// Functions based on dstring_t //
//////////////////////////////////
dstring_t *dstring_init(const char *init_text);
void dstring_free(dstring_t *s);
void dstring_append(dstring_t *s, const char *suffix);

////////////////
// Deprecated //
////////////////
const char *str_find(const char *haystack, const char *needle);
char *str_reverse(char *str);
char *str_to_upper(char *s);
size_t str_count(const char *s, const char *substr);
char **str_split(const char *s, char delimiter, size_t *count);
char *str_trim(const char *s);

#endif
