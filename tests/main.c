#include <stdio.h>
#include "string_utils.h"
#include "test_utils.h"

int main()
{
    // str_length
    if (test_str_length() == 1)
    {
        printf("Failed: str_length\n");
        return 1;
    }

    // str_copy
    if (test_str_copy() == 1)
    {
        printf("Failed: str_copy\n");
        return 1;
    }

    printf("Success!\n");

    return 0;
}
