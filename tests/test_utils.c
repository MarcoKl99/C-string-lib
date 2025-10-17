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
