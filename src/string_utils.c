#include "string_utils.h"
#include "dtypes.h"
#include <stdio.h>

///////////////////////////////////////
// Utility functions based on char * //
///////////////////////////////////////
size_t str_length(const char *str)
{
    if (!str) return 0;

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
    if (!s)
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


//////////////////////////////////
// Functions based on dstring_t //
//////////////////////////////////
dstring_t *dstring_init(const char *init_text)
{
    dstring_t *s = malloc(sizeof(dstring_t));
    if (!s) return NULL;

    if (init_text)
    {
        // Init text was given
        s->length = str_length(init_text);
        s->capacity = (s->length + 1 > STR_INIT_CAPACITY) ? s->length + 1 : STR_INIT_CAPACITY;
        s->data = malloc(s->capacity);
        
        // Check if data was successfully initialized
        if (!s->data)
        {
            free(s);
            return NULL;
        }

        // Copy the init text to the dstrings data
        str_copy(init_text, s->data);
    }
    else
    {
        // No init text was given -> init empty
        s->length = 0;
        s->capacity = STR_INIT_CAPACITY;
        s->data = malloc(s->capacity);
        if (!s->data)
        {
            free(s);
            return NULL;
        }
        s->data[0] = '\0';
    }

    return s;
}

void dstring_free(dstring_t *s)
{
    // Check for NULL value
    if (!s) return;

    // Free the data
    free(s->data);

    // Avoid dangling pointers -> reset the values
    s->data = NULL;
    s->length = 0;
    s->capacity = 0;

    // Free the object itself
    free(s);
}

void dstring_append(dstring_t *s, const char *suffix)
{
    if (!s || !suffix) return;

    // Check the new required capacity
    size_t l_add = str_length(suffix);
    size_t l_new = s->length + l_add;

    // Check if the data must be reallocated
    if (s->capacity < (l_new + 1))
    {
        size_t new_capacity = s->capacity * 2;
        while (new_capacity < l_new + 1)
            new_capacity *= 2;

        char *tmp = realloc(s->data, new_capacity);
        if (!tmp)
            return;

        s->data = tmp;
        s->capacity = new_capacity;
    }

    // Write the old data
    for (size_t i = 0; i < l_add; i++)
    {
        s->data[s->length + i] = suffix[i];
    }

    // Terminate the local concat string
    s->length = l_new;
    s->data[s->length] = '\0';
}

void dstring_reverse(dstring_t *str)
{
    // Check if the data char * is NULL
    if (!str->data) return;

    for (size_t i = 0; i < str->length / 2; i++)
    {
        // Define the lower and upper idx to swap values
        size_t lower = i;
        size_t upper = str->length - i - 1;

        // Swap
        char tmp = str->data[lower];
        str->data[lower] = str->data[upper];
        str->data[upper] = tmp;
    }
}

void dstring_to_upper(dstring_t *s)
{
    // Check for NULL
    if (!s->data) return;

    // Iterate and modify data
    for (size_t i = 0; i < s->length; i++)
    {
        if (s->data[i] >= 'a' && s->data[i] <= 'z')
        {
            // Is lowercase in the original data
            s->data[i] = s->data[i] - ('a' - 'A');
        }
    }
}


void dstring_trim(dstring_t *s)
{
    // Null pointer check
    if (!s) return;

    // Trim trailing whitespaces
    size_t end_idx = s->length - 1;
    while (s->data[end_idx] == ' ')
    {
        end_idx--;
    }

    // Set the terminate char and the new length
    s->data[end_idx + 1] = '\0';
    s->length = end_idx + 1;

    // Trim leading whitespaces
    size_t start_idx = 0;
    while (s->data[start_idx] == ' ')
    {
        start_idx++;
    }

    // Set the new data and length
    s->data += start_idx;
    s->length = s->length - start_idx;
}

void dstring_insert(dstring_t *s, char *s_insert, size_t insert_after_idx)
{
    // Check if the argument insert_after_idx makes sense
    if (insert_after_idx > s->length - 1) return;

    // Null pointer check
    if (!s) return;
    if (!s_insert) return;

    // Check, if new capacity must be allocated
    size_t l_insert = str_length(s_insert);
    size_t required_capacity = s->length + l_insert;
    if (s->capacity < required_capacity * 2)
    {
        // Reallocate new capacity
        while (s->capacity < required_capacity * 2)
        {
            s->capacity *= 2;
        }

        // Reallocate
        char *tmp = realloc(s->data, s->capacity);
        if (!tmp) return;

        s->data = tmp;
    }

    // Push the char back by the length of the given s_insert
    for (size_t i = s->length; i > insert_after_idx; i--)
    {
        s->data[i + l_insert] = s->data[i];
    }

    // We just made some space for s_insert to fit at the given index
    for (size_t i = 0; i < l_insert; i++)
    {
        s->data[insert_after_idx + 1 + i] = s_insert[i];
    }
}
