#include <stdio.h>
#include "string_utils.h"

int main()
{
    // Declare a string variable in different ways

    // 1. Read/Write on the stack
    char str[] = "Hello";
    printf("%d\n", str_length(str));

    return 0;
}
