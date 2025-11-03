#include "dstring_utils.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>


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
    }
    else
    {
        // No init text was given -> init empty
        s->length = 0;
        s->capacity = STR_INIT_CAPACITY;
    }

    s->data = malloc(s->capacity);

    // Check if data was successfully initialized
    if (!s->data)
    {
        free(s);
        return NULL;
    }

    if (init_text) str_copy(init_text, s->data, s->capacity);
    else s->data[0] = '\0';

    return s;
}

dstring_t *dstring_from_file(const char *filepath)
{
    // Check for NULL
    if (!filepath) return NULL;

    FILE *f = fopen(filepath, "r");
    if (!f) return NULL;

    // Determine the size of the file
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    if (fsize < 0 || (unsigned long)fsize > SIZE_MAX)
    {
        fclose(f);
        return NULL;
    }
    rewind(f);

    // Check that the file is not too big
    if ((size_t)fsize > DSTRING_MAX_FILE_SIZE)
    {
        fclose(f);
        return NULL;
    }

    // Create the dstring_t instance from the file's content
    dstring_t *s = malloc(sizeof(dstring_t));
    if (!s)
    {
        fclose(f);
        return NULL;
    }

    s->capacity = (size_t)fsize + 1;
    s->data = malloc(s->capacity);
    if (!s->data)
    {
        free(s);
        fclose(f);
        return NULL;
    }

    // Read the content of the file
    size_t read_bytes = fread(s->data, 1, fsize, f);

    // Check if the read bytes are the expected
    if (read_bytes < (size_t)fsize && ferror(f))
    {
        free(s->data);
        free(s);
        fclose(f);
        return NULL;
    }
    fclose(f);

    // Terminate the string
    s->data[read_bytes] = '\0';
    s->length = read_bytes;

    return s;
}

int dstring_to_file(dstring_t *s, char *filepath)
{
    // Check for NULLs
    if (!s || !filepath) return -1;

    // CHeck that the dstring size is not too big
    if (s->length > DSTRING_MAX_FILE_SIZE) return -1;

    FILE *f = fopen(filepath, "wb");
    if (!f) return -1;

    size_t written = fwrite(s->data, 1, s->length, f);
    fclose(f);

    // Check if all data has been written to the file
    if (written != s->length) return -1;

    return 0;
}

void dstring_free(dstring_t **s)
{
    // Check for NULL value
    if (!s || !(*s)) return;

    // Free the data
    free((*s)->data);
    free(*s);
    
    // Note: Here we reset the s-pointer of the caller -> No dangling pointer anymore
    *s = NULL;
}

void dstring_set(dstring_t *s, char *str)
{
    // Check for NULL
    if (!s || !str) return;

    // Check for self invocation
    if (s->data == str) return;

    // Reallocate if needed
    size_t new_cap = str_length(str) + 1;
    if (new_cap > s->capacity)
    {
        char *tmp = realloc(s->data, new_cap);
        if (!tmp) return;

        s->data = tmp;
        s->capacity = new_cap;
    }

    // Set the new string
    size_t l_new = str_length(str);
    for (size_t i = 0; i < l_new; i++)
    {
        s->data[i] = str[i];
    }

    // Set the terminator
    s->data[l_new] = '\0';

    // Set the new length
    s->length = l_new;
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
            s->data[i] -= ('a' - 'A');
        }
    }
}

void dstring_to_lower(dstring_t *s)
{
    // Check for NULL
    if (!s) return;

    // Iterate and modify data
    for (size_t i = 0; i < s->length; i++)
    {
        if (s->data[i] >= 'A' && s->data[i] <= 'Z')
        {
            // Is uppercase in the original data
            s->data[i] += ('a' - 'A');
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

void dstring_replace(dstring_t *s, char *substr, char *replacement)
{
    // Check for NULLs
    if (!s || !substr || !replacement ) return;

    // Get the pointer to the first substr occurrence
    if (!str_find(s->data, substr)) return;  // No occurrences found in the string

    // Check if we need to reallocate
    size_t len_substr = str_length(substr);
    size_t len_replacement = str_length(replacement);
    size_t new_len = s->length - len_substr + len_replacement;

    if (s->capacity < new_len + 1)
    {
        // Calculate the new capacity
        while (s->capacity < new_len * 2)
        {
            s->capacity *= 2;
        }

        // Reallocate
        s->data = realloc(s->data, s->capacity);
        if (!s->data) return;
    }

    // After reallocating -> determine the pointer to the start of the substr
    char *substr_occurrence = str_find(s->data, substr);

    // Make enough space for the replacement
    int shift = len_replacement - len_substr;

    // Cases: 1 shift > 0, 2 shift < 0, 3 shift == 0
    if (shift > 0)
    {
        // Chars must be shifted to the right
        char *p = &s->data[s->length];

        while (p != substr_occurrence)
        {
            // Shift to the right
            *(p + shift) = *p;
            p--;
        }
    }
    else if (shift < 0)
    {
        // Chars must be shifted to the left -> Start at the end of the found substr and move to the end
        char *p = substr_occurrence + len_substr;

        // Shift
        size_t i = 0;
        while (*(p + i - 1) != '\0')
        {
            *(p + i + shift) = *(p + i);
            i++;
        }
    }

    // Insert the replacement
    for (size_t i = 0; i < len_replacement; i++)
    {
        *(substr_occurrence + i) = replacement[i];
    }

    // Set the new length
    s->length = new_len;
}
