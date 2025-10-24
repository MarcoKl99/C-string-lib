#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "string_utils.h"
#include "pair.h"

// Utility function
int str_are_equal(const char *str_1, const char *str_2)
{
    while (*str_1 != '\0' && *str_2 != '\0')
    {
        if (*str_1 != *str_2)
        {
            return 0;
        }
        str_1++;
        str_2++;
    }

    // If lengths differ
    if (*str_1 != *str_2)
    {
        return 0;
    }

    return 1;
}

// Function tests
int str_length_success()
{
    printf("Testing str_length...\n");

    // Create a list of test pairs
    Pair pairs[] = {
        {"Hello", 5},
        {"Is this working?", 16},
        {"Another example that might be a little bit longer!!!", 52},
        {"60b28b9b-0c2b-4ac0-882b-66b89d26b9e9", 36},
        {"string with     mul  ti     ple whitespa  ce  s", 47},
        {"", 0},
    };

    // Iterate and test all pairs
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    for (int i = 0; i < num_pairs; i++)
    {
        int len = str_length(pairs[i].key);
        int desired_len = pairs[i].value;

        if (len != desired_len)
        {
            return 0;
        }
    }

    return 1;
}

int str_copy_success()
{
    printf("Testing str_copy...\n");

    // Define test strings
    char *test_strs[] = {
        "Hello World",
        "This is another string to be copied!",
        "60b28b9b-0c2b-4ac0-882b-66b89d26b9e9",
        "string with     mul  ti     ple whitespa  ce  s",
    };

    // Iterate and test
    int num_test_strs = sizeof(test_strs) / sizeof(test_strs[0]);
    for (int i = 0; i < num_test_strs; i++)
    {
        char *src = test_strs[i];
        char dest[100];
        str_copy(src, dest);
        if (!str_are_equal(src, dest))
        {
            return 0;
        }
    }

    return 1;
}

int str_concat_success()
{
    printf("Testing str_concat...\n");

    // Initialize variables
    char s1[] = "Hello";
    char s2[] = " World!";
    char concat[] = "Hello World!";

    // Case 1: Happy Path (buffer large enough)
    char buf[100];
    size_t needed = str_concat(s1, s2, buf, 100);

    // Check if the eeded space is correct
    if (needed != str_length(concat))
    {
        return 0;
    }

    // Check buf against concat
    if (!str_are_equal(buf, concat))
    {
        return 0;
    }

    return 1;
}
