#include "env_parser.h"

#include "dtypes.h"
#include "string_utils.h"

env_t *load_env(const char *filepath)
{
    // Check for NULL
    if (!filepath) return NULL;

    // Open the file
    FILE *f = fopen(filepath, "r");
    if (!f) return NULL;

    // Create an empty env_t instance
    env_t *env = (env_t *)malloc(sizeof(env_t));
    if (!env)
    {
        fclose(f);
        return NULL;
    }

    env->keys = NULL;
    env->values = NULL;
    env->count = 0;

    // Process the file line by line (limit of 1024 chars per line)
    char line[1024];
    while (fgets(line, sizeof(line), f))
    {
        // Remove newline character
        size_t len = str_length(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        {
            line[len - 1] = '\0';
        }

        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\0') continue;

        // Split key=value
        size_t num_elements;
        char **split = str_split(line, '=', &num_elements);

        // Check if only 2 elements have been found
        if (num_elements != 2)
        {
            free(env);
            fclose(f);
            return NULL;
        }

        char *key = split[0];
        char *value = split[1];

        // Reallocate keys and values
        env->keys = (char **)realloc(env->keys, (sizeof(char *)) * (env->count + 1));
        if (!env->keys)
        {
            free(env);
            fclose(f);
            return NULL;
        }
        env->values = (char **)realloc(env->values, (sizeof(char *)) * (env->count + 1));
        if (!env->values)
        {
            free(env->keys);
            free(env);
            fclose(f);
            return NULL;
        }

        // Append the new key and value to the lists
        env->keys[env->count] = key;
        env->values[env->count] = value;
        env->count++;
    }

    // Close the file and return the result
    fclose(f);
    return env;
}
