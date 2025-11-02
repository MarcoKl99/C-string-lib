#include "env_parser_tests.h"
#include "env_parser.h"
#include "string_utils.h"

#include "sexyness.h"

int test_env_parser()
{
    printf(BLUE "\nTesting load_env...\n" RESET);

    // Load the example map
    char *path = "data/env.example";
    env_t *env = load_env(path);
    if (!env)
    {
        printf(RED "\t🔴 Failed: Could not load file %s\n" RESET, path);
        return 0;
    }

    // Set the ground truth to compare against
    size_t env_count_should_be = 5;
    char *keys_should_be[] = {
        "SENDER_NAME",
        "SENDER_EMAIL",
        "RECEIVER_NAME",
        "RECEIVER_EMAIL",
        "PROJECT_NAME",
    };
    char *values_should_be[] = {
        "Alice",
        "alice@example.com",
        "Bob",
        "bob@example.com",
        "C-String-Lib",
    };

    // Check the number of returned keys / values
    if (env->count != env_count_should_be)
    {
        printf(RED "\t🔴 Failed: env count = %zu (should be %zu)\n" RESET, env->count, env_count_should_be);
        return 0;
    }

    // Iterate and check the contents
    for (size_t i = 0; i < env->count; i++)
    {
        // Check the key
        if (!str_equal(env->keys[i], keys_should_be[i]))
        {
            printf(RED "\t🔴 Failed: Key mismatch %s != %s\n" RESET, env->keys[i], keys_should_be[i]);
            return 0;
        }

        // Check the value
        if (!str_equal(env->values[i], values_should_be[i]))
        {
            printf(RED "\t🔴 Failed: Value mismatch %s != %s\n" RESET, env->values[i], values_should_be[i]);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
