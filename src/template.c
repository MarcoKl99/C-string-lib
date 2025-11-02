#include "template.h"
#include "string_utils.h"
#include "dstring_utils.h"

#include <stdio.h>

void tempalte_single_replace(dstring_t *s, char *key, char *value)
{
    // Check NULL
    if (!s || !key || !value) return;

    // Build the placeholder for the key
    size_t key_length = str_length(key);
    char *placeholder = malloc(key_length + 4);

    // Fill the placeholder with the key
    placeholder[0] = '{';
    placeholder[1] = '{';

    for (size_t i = 0; i < key_length; i++)
    {
        placeholder[2 + i] = key[i];
    }

    placeholder[key_length + 2] = '}';
    placeholder[key_length + 3] = '}';

    // Replace all placeholders in the original string
    while (str_find(s->data, placeholder))
    {
        dstring_replace(s, placeholder, value);
    }
}

void template_apply(dstring_t *s, char **keys, char **values, size_t num_params)
{
    // Check for NULLs
    if (!s || !keys || !values) return;

    // Iterate and call the subroutine
    for (size_t i = 0; i < num_params; i++)
    {
        tempalte_single_replace(s, keys[i], values[i]);
    }
}
