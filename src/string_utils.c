#include "string_utils.h"

int str_length(const char *str)
{
    // Init a counter and increment until the '\0' char is found
    int len = 0;
    while (str[len] != '\0')
    {
        len++;

        // To avoid endless loops, stop after a threshold
        if (len == STR_LEN_THRESHOLD)
        {
            return -1;
        }
    }

    return len;
}

char *str_copy(char *dest, const char *src)
{
    // Save where dest begins for return
    char *start = dest;

    // Iterate over src until we find the terminator
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    // Set the terminator at the end of dest
    *dest = '\0';

    return start;
}
