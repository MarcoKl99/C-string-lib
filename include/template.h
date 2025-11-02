#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "dtypes.h"

// Templating functionality for dstrung_t instances!
// This can be used to define tempaltes and fill in values based on specified keys.

void tempalte_single_replace(dstring_t *s, char *key, char *value);
void template_apply(dstring_t *s, char **keys, char **values, size_t num_params);

#endif
