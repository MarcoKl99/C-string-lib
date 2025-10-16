#include <stdio.h>
#include "string_utils.h"

int main()
{
    // Declare a string variable in different ways

    // 1. Read/Write on the stack
    char str[] = "Hello";

    printf("Testing str_length...\n");
    int len = str_length(str);
    if (len != 5)
    {
        return 1;
    }

    printf("All test successful!\n");

    return 0;
}
