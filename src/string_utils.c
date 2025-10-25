#include "string_utils.h"

size_t str_length(const char *str)
{
    // Init a counter and increment until the '\0' char is found
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;

        // Stop if len is larger than what size_t can store
        if (len == SIZE_MAX)
        {
            return -1;
        }
    }

    return len;
}

char *str_copy(const char *src, char *dest)
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

size_t str_concat(const char *s1, const char *s2, char *buf, size_t buf_size)
{
    // Check if s1 and s2 are present
    if (!s1)
    {
        s1 = "";
    }

    if (!s2)
    {
        s2 = "";
    }

    // Determine the sizes of s1 and s2
    size_t len1 = str_length(s1);
    size_t len2 = str_length(s2);

    if (SIZE_MAX - len1 < len2)
    {
        // Signal error
        return SIZE_MAX;
    }

    // Calculate the size that is needed for the operation (without NUL)
    size_t needed = len1 + len2;

    if (buf_size == 0)
    {
        return needed;
    }

    // Calculate the space that can actually be written (keep 1 for NUL at the end)
    size_t space = buf_size - 1;
    size_t buf_idx = 0;

    for (size_t i = 0; i < len1 && buf_idx < space; i++)
    {
        buf[buf_idx] = s1[i];
        buf_idx++;
    }

    for (size_t i = 0; i < len2 && buf_idx < space; i++)
    {
        buf[buf_idx] = s2[i];
        buf_idx++;
    }

    // Write the NUL symbol at the end
    buf[buf_idx] = '\0';

    return needed;
}

int str_equal(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
        {
            return 0;
        }
        s1++;
        s2++;
    }

    // If lengths differ
    if (*s1 != *s2)
    {
        return 0;
    }

    return 1;
}

const char *str_find(const char *haystack, const char *needle)
{
    // Find the needle in the haystack hehe ;)

    // Catch the case that the needle is the empty string
    if (*needle == '\0')
    {
        // Return the haystack pointer, as the empty string is always there... somehow
        return haystack;
    }

    // Initialize current needle position, last started streak, state (is_streak)
    const char *needle_current = needle;
    const char *streak_start = NULL;
    size_t is_streak = 0;

    // Iterate through the haystack and search for a match in the first character
    while (*haystack != '\0')
    {
        // Check against the current needle position
        if (*haystack == *needle_current)
        {
            if (!is_streak)
            {
                // Start the streak
                is_streak = 1;
                streak_start = haystack;
            }
            needle_current++;
        }
        else
        {
            if (is_streak)
            {
                // Reset the streak
                streak_start = NULL;
                is_streak = 0;
                needle_current = needle;
            }
        }

        // Check if the entire string has been found
        if (*needle_current == '\0')
        {
            // Terminate
            return streak_start;
        }

        haystack++;
    }

    return NULL;
}
