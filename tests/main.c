#include <stdio.h>
#include "string_utils.h"
#include "test_utils.h"

int main()
{
    // str_equal
    if (!str_equal_success())
    {
        printf("Failed: str_equal\n");
        return 1;
    }

    // str_length
    if (!str_length_success())
    {
        printf("Failed: str_length\n");
        return 1;
    }

    // str_copy
    if (!str_copy_success())
    {
        printf("Failed: str_copy\n");
        return 1;
    }

    // str_concat
    if (!str_concat_success())
    {
        printf("Failed: str_concat\n");
        return 1;
    }

    // str_find
    if (!str_find_success())
    {
        printf("Failed: str_find...\n");
        return 1;
    }

    // str_reverse
    if (!str_reverse_success())
    {
        printf("Failed: str_reverse...\n");
        return 1;
    }

    printf("Success!\n");

    return 0;
}
