#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "dtypes.h"

#define DEFAULT_PLACEHOLDER_VALUE "UNKNOWN";

char *_get_value_for_key(char *key, env_t *env);
char *_get_next_placeholder(dstring_t *s);
void _set_key_transform_tuple(KeyTransformTuple *t, char *placeholder);
void template_apply(dstring_t *s, env_t *env);

#endif
