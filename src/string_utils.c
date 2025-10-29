#include "string_utils.h"
#include <stdio.h>

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
    // Check if one of the pointers is NULL
    if (s1 == NULL && s2 != NULL)
    {
        return 0;
    }

    if (s2 == NULL && s1 != NULL)
    {
        return 0;
    }

    if (s1 == NULL && s2 == NULL)
    {
        return 1;
    }

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

char *str_reverse(char *str)
{
    // Protect against NULL pointer
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = str_length(str);
    char *rev = malloc(len + 1); // +1 due to '\0' at the end

    // Secure against memory errors
    if (!rev)
    {
        return NULL;
    }

    // Assign the chars in switched order
    for (int i = 0; i < len; i++)
    {
        rev[i] = str[len - 1 - i];
    }
    rev[len] = '\0';

    return rev;
}

char *str_to_upper(char *s)
{
    // Catch the case of NULL pointer
    if (s == NULL)
    {
        return NULL;
    }

    // Allocate memory on the heap for the new string (avoids read-only problems with string literals)
    char *s_upper = malloc(str_length(s) + 1);  // + 1 due to '\0'

    // Save the init pointer to return later
    char *res_p = s_upper;

    while (*s != '\0')
    {
        // Check if the char lies in the uppercase part of ASCII
        if (*s >= 'a' && *s <= 'z')
        {
            // Set the uppercase value in the ASCII table
            *s_upper = *s - ('a' - 'A');
        }
        else
        {
            // Char is already upper case
            *s_upper = *s;
        }

        s++;
        s_upper++;
    }

    return res_p;
}

size_t str_count(const char *s, char c)
{
    if (!s) return 0;

    size_t count = 0;

    while (*s != '\0')
    {
        if (*s == c)
        {
            count++;
        }

        s++;
    }

    return count;
}

char **str_split(const char *s, char delimiter, size_t *count)
{
    // Catch the case of the null pointer
    if (!s)
    {
        if (count) *count = 0;
        return NULL;
    }

    // Count the number of required tokens (substrings)
    size_t num_tokens = str_count(s, delimiter) + 1;

    // Create a list of sizes of the tokens
    size_t *sizes = malloc(num_tokens * sizeof(size_t));
    if (!sizes)
    {
        if (count) *count = 0;
        return NULL;
    }

    // Fill the sizes of the tokens
    size_t size_token = 0, idx = 0;
    for (const char *p = s; ; p++)
    {
        if (*p == delimiter || *p == '\0')
        {
            // Save the current size of the token
            sizes[idx++] = size_token;

            // Reset the size for the next token
            size_token = 0;

            // Break if the string is at the end
            if (*p == '\0') break;
        }
        else
        {
            // Do not increase the size token at the delimiter! -> Only here when another char was found
            size_token++;
        }
    }

    // Allocate the size for the array of tokens
    char **tokens = malloc(num_tokens * sizeof(char *));
    if (!tokens)
    {
        free(sizes);
        if (count) *count = 0;
        return NULL;
    }

    // Iterate through the string again and save the corresponding tokens
    size_t offset = 0;
    for (size_t i = 0; i < num_tokens; i++)
    {
        // Allocate memory for the token on the heap
        char *token = malloc((sizes[i] + 1) * sizeof(char));
        if (!token)
        {
            // Free all previously allocated tokens
            for (size_t j = 0; j < i; j++)
            {
                free(tokens[j]);
            }

            // Reset the rest and return NULL
            free(tokens);
            free(sizes);
            if (count) *count = 0;
            return NULL;
        }

        char *token_start = token;
        for (size_t k = 0; k < sizes[i]; k++)
        {
            token[k] = s[offset + k];
        }
        token[sizes[i]] = '\0';

        offset += sizes[i] + 1;
        tokens[i] = token_start;
    }

    // Set the number of tokens to the count variable via the passed pointer
    if (count) *count = num_tokens;

    // Free the sizes array
    free(sizes);

    return tokens;
}

char *str_trim(const char *s)
{
    // Null pointer check
    if (!s)
        return NULL;

    // Sace the indices from and to which the trimmed string spans
    int num_leading_ws = 0;
    int num_trailing_ws = 0;

    // Determine the number of leading whitespaces
    const char *tmp = s;
    while (*tmp == ' ')
    {
        num_leading_ws++;
        tmp++;
    }

    // Determine the number of trailing whitespaces
    tmp = s + str_length(s) - 1;
    while (*tmp == ' ')
    {
        num_trailing_ws++;
        tmp--;
    }

    // Create the new string
    int new_len = str_length(s) - num_leading_ws - num_trailing_ws;

    // Catch case of negative new len
    if (new_len < 0)
    {
        new_len = 0;
    }

    char *trimmed = malloc((new_len + 1) * sizeof(char));
    if (!trimmed)
        return NULL;

    // Fill the trimmed string
    for (size_t i = 0; i < new_len; i++)
    {
        trimmed[i] = s[num_leading_ws + i];
    }
    trimmed[new_len] = '\0';

    return trimmed;
}
