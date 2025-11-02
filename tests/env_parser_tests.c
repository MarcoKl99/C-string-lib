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

    size_t env_count_should_be = 2;
    if (env->count != env_count_should_be)
    {
        printf(RED "\t🔴 Failed: env count = %zu (should be %zu)\n" RESET, env->count, env_count_should_be);
        return 0;
    }

    if (!(str_equal(env->keys[0], "name") && str_equal(env->keys[1], "lang")))
    {
        printf(RED "\t🔴 Failed: %s != %s or %s != %s\n" RESET, env->keys[0], "name", env->keys[1], "lang");
        return 0;
    }

    if (!(str_equal(env->values[0], "Bob") && str_equal(env->values[1], "C")))
    {
        printf(RED "\t🔴 Failed: %s != %s or %s != %s\n" RESET, env->values[0], "Bob", env->values[1], "C");
        return 0;
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
