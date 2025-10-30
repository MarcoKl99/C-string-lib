#include <stdio.h>
#include "string_utils.h"
#include "test_utils.h"

int main()
{
    ////////////////////////////////////////
    // Testing utility functions (char *) //
    ////////////////////////////////////////
    if (!str_length_success())
    {
        printf("Failed: str_length\n");
        return 1;
    }

    if (!str_equal_success())
    {
        printf("Failed: str_equal\n");
        return 1;
    }

    if (!str_copy_success())
    {
        printf("Failed: str_copy\n");
        return 1;
    }

    /////////////////////////////////
    // Testing dstring_t functions //
    /////////////////////////////////
    if (!dstring_append_success())
    {
        printf("Failed: dstring_append\n");
        return 1;
    }

    ////////////////
    // Deprecated //
    ////////////////
    if (!str_find_success())
    {
        printf("Failed: str_find...\n");
        return 1;
    }

    if (!str_reverse_success())
    {
        printf("Failed: str_reverse...\n");
        return 1;
    }

    if (!str_to_upper_success())
    {
        printf("Failed: str_to_upper...\n");
        return 1;
    }

    if (!str_count_success())
    {
        printf("Failed: str_count...\n");
        return 1;
    }

    if (!str_split_success())
    {
        printf("Failed: str_split...\n");
        return 1;
    }

    if (!str_trim_success())
    {
        printf("Failed: str_trim...\n");
        return 1;
    }

    printf("Success!\n");

    return 0;
}
