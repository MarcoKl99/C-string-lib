#include "string_utils.h"
#include "dtypes.h"
#include <stdio.h>

///////////////////////////////////////
// Utility functions based on char * //
///////////////////////////////////////
size_t str_length(const char *str)
{
    // Check for NULLs
    if (!str) return 0;

    // Init a counter and increment until the '\0' char is found
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;

        // Stop if len is larger than what size_t can store
        if (len == SIZE_MAX)
        {
            return 0;
        }
    }

    return len;
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

    size_t counter = 0;
    while (*s1 != '\0' && *s2 != '\0' && counter < SIZE_MAX)
    {
        if (*s1 != *s2)
        {
            return 0;
        }
        s1++;
        s2++;
        counter++;
    }

    // If lengths differ
    if (*s1 != *s2)
    {
        return 0;
    }

    return 1;
}

void str_copy(const char *src, char *dest, size_t dest_size)
{
    // Check for NULLs
    if (!src || !dest || dest_size == 0) return;

    // Iterate over src until we find the terminator
    size_t i = 0;
    while (src[i] != '\0' && i < dest_size - 1)
    {
        dest[i] = src[i];
        i++;
    }

    // Set the terminator at the end of dest
    dest[i] = '\0';
}

char *str_find(char *haystack, char *needle)
{
    // Find the needle in the haystack hehe ;)

    // Check for NULLs
    if (!haystack || !needle) return NULL;

    // Catch the case that the needle is the empty string
    if (*needle == '\0')
    {
        // Return the haystack pointer, as the empty string is always there... somehow
        return haystack;
    }

    // Initialize current needle position, last started streak, state (is_streak)
    char *needle_current = needle;
    char *streak_start = NULL;
    size_t is_streak = 0;

    // Iterate through the haystack and search for a match in the first character
    size_t counter = 0;
    while (*haystack != '\0')
    {
        // Check for too long loops
        if (counter == SIZE_MAX) return NULL;
        counter++;

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

        // if (is_streak) printf("Haystack: %c - Needle current: %c\n", *haystack, *needle_current);

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

size_t str_count(const char *s, const char *substr)
{
    // Catch NULL pointers
    if (!s || !substr)
        return 0;

    // Resetable pointer for the substring to search for and number of occurences
    const char *substr_sp = substr;
    size_t num_occurences = 0;

    while (*s != '\0')
    {
        // Check if we are at the position of a substr occurence
        if (*s == *substr_sp)
        {
            substr_sp++;
        }
        else
        {
            // Reset
            substr_sp = substr;
        }

        if (*substr_sp == '\0')
        {
            // Found the entire substr! Increase counter and reset search pointer
            num_occurences++;
            substr_sp = substr;
        }
        s++;
    }

    return num_occurences;
}

char **str_split(const char *s, char delimiter, size_t *count)
{
    // Catch the case of the null pointer
    if (!s || str_length(s) == 0)
    {
        if (count) *count = 0;
        return NULL;
    }

    // Make the delimtier char a string for the str_count function
    char delimiter_str[2];
    delimiter_str[0] = delimiter;
    delimiter_str[1] = '\0';

    // Count the number of required tokens (substrings)
    size_t num_tokens = str_count(s, delimiter_str) + 1;

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

char *str_substr(const char *src, size_t from_idx, size_t to_idx)
{
    // Check for NULLs
    if (!src) return NULL;

    // Check that the to_idx is larger or equal than the from_idx
    if (to_idx < from_idx) return NULL;

    // Catch the case that the indexes are equal
    if (from_idx == to_idx) return NULL;

    // Check if the indices are not-negative
    if (from_idx < 0 || to_idx < 0) return NULL;

    // Check if the indices are within the range of the string
    size_t len_src = str_length(src);
    if (from_idx < 0 || len_src < to_idx) return NULL;

    // Create the proper substring
    size_t len = to_idx - from_idx;
    char *substr = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        substr[i] = src[from_idx + i];
    }

    // Terminate the string
    substr[len] = '\0';

    return substr;
}

char *str_to_upper(char *s)
{
    // Check for NULLs
    if (!s) return NULL;

    size_t len_s = str_length(s);
    char *s_upper = malloc(len_s + 1);
    if (!s_upper) return NULL;

    for (size_t i = 0; i < len_s; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // Is lowercase in the original data
            s_upper[i] = s[i] - ('a' - 'A');
        }
        else
        {
            s_upper[i] = s[i];
        }
    }
    s_upper[len_s] = '\0';

    return s_upper;
}

char *str_to_lower(char *s)
{
    // Check for NULLs
    if (!s) return NULL;

    size_t len_s = str_length(s);
    char *s_lower = malloc(len_s + 1);
    if (!s_lower) return NULL;

    for (size_t i = 0; i < len_s; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            // Is lowercase in the original data
            s_lower[i] = s[i] + ('a' - 'A');
        }
        else
        {
            s_lower[i] = s[i];
        }
    }
    s_lower[len_s] = '\0';

    return s_lower;
}
