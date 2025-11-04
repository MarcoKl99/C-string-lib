#ifndef ENV_PARSER_H
#define ENV_PARSER_H

#include <stdio.h>
#include "dtypes.h"

env_t *load_env(const char *filepath);
void free_env(env_t *env);

#endif
