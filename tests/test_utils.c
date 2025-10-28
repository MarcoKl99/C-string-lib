#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "string_utils.h"

// Types
#include "pair.h"
#include "string_tuple.h"

// Function tests
int str_length_success()
{
    printf("Testing str_length...\n");

    // Create a list of test pairs
    Pair pairs[] = {
        {"Hello", 5},
        {"Is this working?", 16},
        {"Another example that might be a little bit longer!!!", 52},
        {"60b28b9b-0c2b-4ac0-882b-66b89d26b9e9", 36},
        {"string with     mul  ti     ple whitespa  ce  s", 47},
        {"", 0},
    };

    // Iterate and test all pairs
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    for (int i = 0; i < num_pairs; i++)
    {
        int len = str_length(pairs[i].key);
        int desired_len = pairs[i].value;

        if (len != desired_len)
        {
            return 0;
        }
    }

    return 1;
}

int str_copy_success()
{
    printf("Testing str_copy...\n");

    // Define test strings
    char *test_strs[] = {
        "Hello World",
        "This is another string to be copied!",
        "60b28b9b-0c2b-4ac0-882b-66b89d26b9e9",
        "string with     mul  ti     ple whitespa  ce  s",
    };

    // Iterate and test
    int num_test_strs = sizeof(test_strs) / sizeof(test_strs[0]);
    for (int i = 0; i < num_test_strs; i++)
    {
        char *src = test_strs[i];
        char dest[100];
        str_copy(src, dest);
        if (!str_equal(src, dest))
        {
            return 0;
        }
    }

    return 1;
}

int str_concat_success()
{
    printf("Testing str_concat...\n");

    // Initialize variables
    char s1[] = "Hello";
    char s2[] = " World!";
    char concat[] = "Hello World!";

    // Case 1: Happy Path (buffer large enough)
    size_t buf_size = 100;
    char buf[buf_size];
    size_t needed = str_concat(s1, s2, buf, buf_size);

    // Check if the eeded space is correct
    if (needed != str_length(concat))
    {
        return 0;
    }

    // Check that the needed size is smaller than the buf_size
    if (needed >= buf_size)
    {
        return 0;
    }

    // Check buf against concat
    if (!str_equal(buf, concat))
    {
        return 0;
    }

    // Case 2: Buffer too small
    buf_size = 3;
    char buf_small[buf_size];
    needed = str_concat(s1, s2, buf_small, buf_size);

    // Check that the required space is more than buf_size -> indicate error
    if (needed <= buf_size)
    {
        return 0;
    }

    // Check that the string was not written in the too small buffer
    if (str_equal(buf_small, concat))
    {
        return 0;
    }

    // Success - all tests passed
    return 1;
}

int str_equal_success()
{
    printf("Testing str_equal...\n");

    // Define sample strings to test on
    char *strings[] = {
        "Hello",
        "   ",
        "This is a longer text!",
        "",
    };
    int num_samples = sizeof(strings) / sizeof(strings[0]);

    // Iterate and check against themselves -> should be true
    for (int i = 0; i < num_samples; i++)
    {
        // Check against all strings - the same must return 1, all others 0
        for (int k = 0; k < num_samples; k++)
        {
            int equal = str_equal(strings[i], strings[k]);
            int desired;

            if (i == k)
            {
                desired = 1;
            }
            else
            {
                desired = 0;
            }

            if (equal != desired)
            {
                return 0;
            }
        }
    }

    return 1;
}

int str_find_success()
{
    printf("Testing str_find...\n");

    // Define test data for matches
    const StringTuple test_data_match[] = {
        {"Hello", "He"},
        {"This is a beautiful text that we read here thank you for reading!", "text that "},
        {"Programming", "gram"},
        {"Any random string", ""},
        {"", ""},
    };

    size_t num_matches = sizeof(test_data_match) / sizeof(test_data_match[0]);

    for (int i = 0; i < num_matches; i++)
    {
        const char *found = str_find(test_data_match[i].s1, test_data_match[i].s2);
        if (found == NULL)
        {
            // Should have found that - return false
            return 0;
        }
    }

    const StringTuple test_data_mismatch[] = {
        {"Have a great day!", "abc"},
        {"What is this test even?", "!"},
        {"ckjsdhgtisr", "solar system (WHAT?)"},
        {"", "a"},
    };

    size_t num_mismatches = sizeof(test_data_mismatch) / sizeof(test_data_mismatch[0]);

    for (int i = 0; i < num_mismatches; i++)
    {
        const char *found = str_find(test_data_mismatch[i].s1, test_data_mismatch[i].s2);
        if (found != NULL)
        {
            // Was found but should not be there - return false
            return 0;
        }
    }

    return 1;
}

int str_reverse_success()
{
    printf("Testing str_reverse...\n");

    // Check for NULL pointer
    if (str_reverse(NULL) != NULL)
    {
        return 0;
    }

    // Define test data
    StringTuple test_data[] = {
        {"Hello", "olleH"},
        {"123", "321"},
        {" ", " "},
        {"This text right here is a little bit longer! ...Nice ;)", "); eciN... !regnol tib elttil a si ereh thgir txet sihT"},
        {"anna", "anna"},
    };

    // Check the individual test datapoints
    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);
    for (int i = 0; i < num_test_data; i++)
    {
        char *rev = str_reverse(test_data[i].s1);

        // Check for null pointer
        if (!rev)
        {
            return 0;
        }

        // Check that the reversed string is the correct one
        if (!str_equal(rev, test_data[i].s2))
        {
            free(rev);
            return 0;
        }

        // Free the allocated memory from this test run
        free(rev);
    }

    return 1;
}

int str_to_upper_success()
{
    printf("Testing str_to_upper...\n");

    // Create test data
    StringTuple test_data[] = {
        {NULL, NULL},
        {"hello", "HELLO"},
        {"UPPER", "UPPER"},
        {"This is a Mix oF lowercAsE and UpperCAse!", "THIS IS A MIX OF LOWERCASE AND UPPERCASE!"},
        {"123", "123"},
        {"!&$", "!&$"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        char *upper = str_to_upper(test_data[i].s1);
        if (!str_equal(upper, test_data[i].s2))
        {
            return 0;
        }

        free(upper);
    }

    return 1;
}
