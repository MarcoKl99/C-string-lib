#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "string_utils.h"

// Utility function
int assert_str_equal(const char *test_name, const char *str_1, const char *str_2)
{
    while (*str_1 != '\0' && *str_2 != '\0')
    {
        if (*str_1 != *str_2)
        {
            return 1;
        }
        str_1++;
        str_2++;
    }

    // If lengths differ
    if (*str_1 != *str_2)
    {
        return 1;
    }

    return 0;
}

// Function tests
int test_str_length()
{
    printf("Testing str_length...\n");
    char str[] = "Hello";
    int len = str_length(str);
    if (len != 5)
    {
        return 1;
    }

    return 0;
}

int test_str_copy()
{
    printf("Testing str_copy...\n");
    char src[] = "Hello World";
    char dest[] = "";
    str_copy(src, dest);
    if (assert_str_equal("str_copy", src, dest))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int test_str_concat()
{
    printf("Testing str_concat...\n");

    // Initialize variables
    char s1[] = "Hello";
    char s2[] = " World!";

    // Case 1: Happy Path (buffer large enough)
    char buf[100];
    size_t needed = str_concat(s1, s2, buf, 100);

    // Check if the eeded space is correct
    if (needed != str_length(s1) + str_length(s2))
    {
        return 1;
    }

    // Create a string index and check s1
    size_t s_idx = 0;
    size_t buf_idx = 0;

    while (s1[s_idx] != '\0')
    {
        if (s1[s_idx] != buf[buf_idx])
        {
            return 1;
        }

        s_idx++;
        buf_idx++;
    }

    // Reset and check s2
    s_idx = 0;

    while (s2[s_idx] != '\0')
    {
        if (s2[s_idx] != buf[buf_idx])
        {
            return 1;
        }

        s_idx++;
        buf_idx++;
    }

    // Check if the string in the buffer ends here
    if (buf[buf_idx] != '\0')
    {
        return 1;
    }

    // Success - return 0
    return 0;
}
