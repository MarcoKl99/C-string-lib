#include <stdlib.h>
#include <stdio.h>
#include "string_tests.h"
#include "string_utils.h"

// Types
#include "dtypes.h"
#include "sexyness.h"


////////////////////////////////////////
// Testing utility functions (char *) //
////////////////////////////////////////
int test_str_length()
{
    printf(BLUE "\nTesting str_length...\n" RESET);

    // Create a list of test pairs
    Pair pairs[] = {
        {"Hello", 5},
        {"Is this working?", 16},
        {"Another example that might be a little bit longer!!!", 52},
        {"60b28b9b-0c2b-4ac0-882b-66b89d26b9e9", 36},
        {"string with     mul  ti     ple whitespa  ce  s", 47},
        {"", 0},
        {NULL, 0},
    };

    // Iterate and test all pairs
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    for (int i = 0; i < num_pairs; i++)
    {
        int len = str_length(pairs[i].key);
        int desired_len = pairs[i].value;

        if (len != desired_len)
        {
            printf(RED "\t🔴 Failed: %d != %d for string %s\n" RESET, len, desired_len, pairs[i].key);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_copy()
{
    printf(BLUE "\nTesting str_copy...\n" RESET);

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
        size_t dest_capacity = 100;
        char dest[dest_capacity];
        str_copy(src, dest, dest_capacity);
        if (!str_equal(src, dest))
        {
            printf(RED "\t🔴 Failed: %s != %s\n" RESET, src, dest);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}


int test_str_equal()
{
    printf(BLUE "\nTesting str_equal...\n" RESET);

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
                printf(RED "\t🔴 Failed: %s =?= %s should be %d but is %d\n", strings[i], strings[k], desired, equal);
                return 0;
            }
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_find()
{
    printf(BLUE "\nTesting str_find...\n" RESET);

    // Define test data for matches
    const StringTuple test_data_match[] = {
        {"Hello", "He"},
        {"This is a beautiful text that we read here thank you for reading!", "text that "},
        {"Programming", "gram"},
        {"Any random string", ""},
        {"", ""},
        {"From: {{SENDER_NAME}} <{{SENDER_EMAIL}}>", "{{SENDER_EMAIL}}"},
    };

    size_t num_matches = sizeof(test_data_match) / sizeof(test_data_match[0]);

    for (int i = 0; i < num_matches; i++)
    {
        const char *found = str_find(test_data_match[i].s1, test_data_match[i].s2);
        if (!found)
        {
            // Should have found that - return false
            printf(RED "\t🔴 Failed: Did not find %s in %s\n", test_data_match[i].s2, test_data_match[i].s1);
            return 0;
        }
    }

    const StringTuple test_data_mismatch[] = {
        {"Have a great day!", "dai"},
        {"What is this test even?", "!"},
        {"ckjsdhgtisr", "solar system (WHAT?)"},
        {"", "a"},
    };

    size_t num_mismatches = sizeof(test_data_mismatch) / sizeof(test_data_mismatch[0]);

    for (int i = 0; i < num_mismatches; i++)
    {
        const char *found = str_find(test_data_mismatch[i].s1, test_data_mismatch[i].s2);
        if (found)
        {
            // Was found but should not be there - return false
            printf(RED "\t🔴 Failed: Found %s in %s\n", test_data_mismatch[i].s2, test_data_mismatch[i].s1);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_count()
{
    printf(BLUE "\nTesting str_count...\n" RESET);

    // Define the test data
    StrCountTestData test_data[] = {
        {"Hello", "l", 2},
        {"Hello", "He", 1},
        {"This is a cool test ;)", " ", 5},
        {"          ", " ", 10},
        {NULL, " ", 0},
        {"Some string", NULL, 0},
        {"This is a cool string where we are looking for cool substrings... cool ;)", "cool", 3},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    size_t count;
    for (size_t i = 0; i < num_test_data; i++)
    {
        count = str_count(test_data[i].s, test_data[i].substr);
        if (count != test_data[i].count)
        {
            printf(RED "\t🔴 Failed: %zu != %zu for %s in %s\n", count, test_data[i].count, test_data[i].substr, test_data[i].s);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_split()
{
    printf(BLUE "\nTesting str_split...\n" RESET);

    // Init the count variable
    size_t count;

    // Define the test data
    const char *tokens1[] = {"Hello", "World"};
    StrSplitTestData td1 = {"Hello World", ' ', 2, tokens1};

    const char *tokens2[] = {"This", "is", "very", "cool", ";)"};
    StrSplitTestData td2 = {"This is very cool ;)", ' ', 5, tokens2};

    const char *tokens3[] = {"", "es", "word"};
    StrSplitTestData td3 = {"testword", 't', 3, tokens3};

    const char *tokens4[] = {"", "nn", ""};
    StrSplitTestData td4 = {"anna", 'a', 3, tokens4};

    const char *tokens5[] = {"a", "", "a"};
    StrSplitTestData td5 = {"anna", 'n', 3, tokens5};

    const char *tokens6[] = {"t", "", "", "", "st"};
    StrSplitTestData td6 = {"teeeest", 'e', 5, tokens6};

    const char *tokens7[] = {""};
    StrSplitTestData td7 = {"", ' ', 0, tokens7};

    const char *tokens8[] = {};
    StrSplitTestData td8 = {NULL, ' ', 0, tokens8};

    // Colelct the defined test data
    StrSplitTestData test_data[] = {td1, td2, td3, td4, td5, td6, td7, td8};
    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    StrSplitTestData td;
    for (size_t i = 0; i < num_test_data; i++)
    {
        td = test_data[i];
        char **split = str_split(td.s, td.delimiter, &count);

        if (count != td.num_tokens){
            printf(RED "\t🔴 Failed: Count = %zu and should be %zu at s = %s\n", count, td.num_tokens, td.s);
            return 0;
        }

        for (size_t k = 0; k < count; k++)
        {
            if (!str_equal(split[k], td.tokens[k]))
            {
                printf(RED "\t🔴 Failed: Token %s != %s\n", split[k], td.tokens[k]);
                return 0;
            }
        }

        for (size_t k = 0; k < count; k++) free(split[k]);
        if (split) free(split);
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_substr()
{
    printf(BLUE "\nTesting str_substr...\n" RESET);

    // Create the test data
    char s_test[] = "This is a test!";
    StrSubstrTestData test_data[] = {
        {"Hello World", 0, 5, "Hello"},
        {"Hello World", 6, 11, "World"},
        {"This is another test", 8, 15, "another"},
        {s_test, 0, str_length(s_test), s_test},
        {NULL, 1, 2, NULL},
        {"Hello", 3, 2, NULL},
        {"", 0, 0, NULL},
        {"Hello", 37, 149, NULL},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    // Iterate and test
    for (size_t i = 0; i < num_test_data; i++)
    {
        StrSubstrTestData td = test_data[i];

        char *substr = str_substr(td.src, td.from_idx, td.to_idx);
        if (!str_equal(substr, td.result))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", substr, td.result);
            return 0;
        }

        free(substr);
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_to_upper()
{
    printf(BLUE "\nTesting str_to_upper...\n" RESET);

    // Define test data
    StringTuple test_data[] = {
        {"hello", "HELLO"},
        {NULL, NULL},
        {"", ""},
        {"!§&/", "!§&/"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        StringTuple td = test_data[i];

        char *upper = str_to_upper(td.s1);

        if (!str_equal(upper, td.s2))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", upper, td.s2);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_str_to_lower()
{
    printf(BLUE "\nTesting str_to_lower...\n" RESET);

    // Define test data
    StringTuple test_data[] = {
        {"HeLlO", "hello"},
        {NULL, NULL},
        {"", ""},
        {"!§&/", "!§&/"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        StringTuple td = test_data[i];

        char *lower = str_to_lower(td.s1);

        if (!str_equal(lower, td.s2))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", lower, td.s2);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
