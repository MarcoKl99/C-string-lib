#ifndef DSTRING_UTILS_H
#define DSTRING_UTILS_H

#include "dtypes.h"
#include <stdlib.h>

#define DSTRING_MAX_FILE_SIZE (10 * 1024 * 1024)

//////////////////////////////////
// Functions based on dstring_t //
//////////////////////////////////
dstring_t *dstring_init(const char *init_text);
dstring_t *dstring_from_file(const char *filepath);
int dstring_to_file(dstring_t *s, char *filepath);

void dstring_free(dstring_t *s);
void dstring_set(dstring_t *s, char *str);

void dstring_append(dstring_t *s, const char *suffix);
void dstring_reverse(dstring_t *str);
void dstring_to_upper(dstring_t *s);
void dstring_to_lower(dstring_t *s);
void dstring_trim(dstring_t *s);
void dstring_insert(dstring_t *s, char *s_insert, size_t insert_after_idx);
void dstring_replace(dstring_t *s, char *substr, char *replacement);

#endif
