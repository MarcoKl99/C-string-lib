#include "template.h"
#include "string_utils.h"
#include "dstring_utils.h"

#include <stdio.h>

char *_get_next_placeholder(dstring_t *s)
{
    // Save the state: 0 = searching start, 1 = found start
    size_t state = 0;
    size_t placeholder_start_idx = 0;
    for (size_t i = 0; i < s->length - 1; i++)  // s->length - 1 to always check for 2 chars in advance
    {
        if (state == 0 && s->data[i] == '{' && s->data[i + 1] == '{')
        {
            // Searching and found beginning of placeholder
            // Set this idx to be the start of the placeholder
            placeholder_start_idx = i;

            // Set state to found start and searching for end
            state = 1;
        }
        else if (state == 1 && s->data[i] == '}' && s->data[i + 1] == '}')
        {
            // Searching and found the end of a placeholder
            char *placeholder = str_substr(s->data, placeholder_start_idx, i + 2);  // str_substr is allowed to go until length!
            // char *key_text = str_substr(placeholder, 2, str_length(placeholder) - 2);

            return placeholder;
        }
    }

    return NULL;
}

char *_get_value_for_key(char *key, env_t *env)
{
    // Get the value for the given key to use
    char *value_to_use = DEFAULT_PLACEHOLDER_VALUE;
    for (size_t i = 0; i < env->count; i++)
    {
        if (str_equal(env->keys[i], key))
        {
            value_to_use = env->values[i];
        }
    }

    return value_to_use;
}

void _set_key_transform_tuple(KeyTransformTuple *t, char *placeholder)
{
    // Get rid of the curly braces
    char *placeholder_content = str_substr(placeholder, 2, str_length(placeholder) - 2);
    if (!placeholder) return;

    // Check if there is a function specified in the placeholder
    string_transform_fn fn = NULL;
    char *key = NULL;
    if (str_find(placeholder_content, ":"))
    {
        // Split the two pieces
        size_t count;
        char **split = str_split(placeholder_content, ':', &count);
        if (count != 2) return;

        char *function_keyword = split[0];
        key = split[1];

        if (str_equal(function_keyword, "upper")) fn = str_to_upper;
        else if (str_equal(function_keyword, "lower")) fn = str_to_lower;
    }
    else
    {
        key = placeholder_content;
    }

    t->fn = fn;
    t->key = key;
}

void template_apply(dstring_t *s, env_t *env)
{
    // Check for NULLs
    if (!s || !env || !env->keys || !env->values) return;

    // Search the next placeholder in the string
    char *next_placeholder = _get_next_placeholder(s);

    while (next_placeholder)
    {
        // Get the name of the key and the transformation function
        KeyTransformTuple key_transform;
        _set_key_transform_tuple(&key_transform, next_placeholder);

        // Check if we got values
        if (!key_transform.key) return;

        // Get the value for the given key to use
        char *value_to_use = _get_value_for_key(key_transform.key, env);

        // Check if we got values
        if (value_to_use)
        {
            if (key_transform.fn) value_to_use = key_transform.fn(value_to_use);
        }
        else value_to_use = DEFAULT_PLACEHOLDER_VALUE;

        // Replace the value
        dstring_replace(s, next_placeholder, value_to_use);

        // Get the next placeholder
        next_placeholder = _get_next_placeholder(s);
    }
}
