#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
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
        char dest[100];
        str_copy(src, dest);
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
    };

    size_t num_matches = sizeof(test_data_match) / sizeof(test_data_match[0]);

    for (int i = 0; i < num_matches; i++)
    {
        const char *found = str_find(test_data_match[i].s1, test_data_match[i].s2);
        if (found == NULL)
        {
            // Should have found that - return false
            printf(RED "\t🔴 Failed: Did not find %s in %s\n", test_data_match[i].s2, test_data_match[i].s1);
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
    StrSplitTestData td7 = {"", ' ', 1, tokens7};

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

        if (count != td.num_tokens) return 0;

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


/////////////////////////////////
// Testing dstring_t functions //
/////////////////////////////////
int test_dstring_append()
{
    printf(BLUE "\nTesting dstring_append...\n" RESET);

    // Define test data
    StringTriple test_data[] = {
        {"Hello", " World", "Hello World"},
        {"Hey this is a litt", "le bit longer of a text!", "Hey this is a little bit longer of a text!"},
        {"", "Hey", "Hey"},
        {"", "", ""},
        {NULL, "Hello", "Hello"},
        {"Hey", NULL, "Hey"},
        {NULL, NULL, ""},
        {"I was", " searching for a seg fault until midnight here!", "I was searching for a seg fault until midnight here!"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        StringTriple t = test_data[i];

        // Create the dstring_t out of the frist one
        dstring_t *s = dstring_init(t.s1);
        dstring_append(s, t.s2);

        int equal = str_equal(s->data, t.s3);
        int correct_length = s->length == str_length(t.s1) + str_length(t.s2);
        int sufficient_capacity = s->length < s->capacity;

        if (!equal || !correct_length || !sufficient_capacity)
        {
            printf(RED "\t🔴 Failed: equal (%d), correct_length (%d), sufficient_capacity (%d)\n", equal, correct_length, sufficient_capacity);
            return 0;
        }

        // Free the dstring_t instance
        dstring_free(s);
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_dstring_reverse()
{
    printf(BLUE "\nTesting dstring_reverse...\n" RESET);

    // Create test data
    StringTuple test_data[] = {
        {"Hello", "olleH"},
        {"1234", "4321"},
        {"123456789", "987654321"},
        {"", ""},
        {" ", " "},
        {"This is a pretty long text right here, right? ;)", "); ?thgir ,ereh thgir txet gnol ytterp a si sihT"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        dstring_t *s = dstring_init(test_data[i].s1);
        if (!s) return 0;

        dstring_reverse(s);

        if (!str_equal(s->data, test_data[i].s2))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, test_data[i].s2);
            return 0;
        }

        dstring_free(s);
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_dstring_to_upper()
{
    printf(BLUE "\nTesting dstring_to_upper...\n" RESET);

    // Define test data
    StringTuple test_data[] = {
        {"Hello", "HELLO"},
        {"THIS IS ALREADY UPPER", "THIS IS ALREADY UPPER"},
        {" ", " "},
        {"&&/()$#*+!", "&&/()$#*+!"},
        {"", ""},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    // Iterate and test
    for (size_t i = 0; i < num_test_data; i++)
    {
        dstring_t *s = dstring_init(test_data[i].s1);
        if (!s) return 0;

        dstring_to_upper(s);

        if (!str_equal(s->data, test_data[i].s2))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, test_data[i].s2);
            return 0;
        }

        dstring_free(s);
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_dstring_trim()
{
    printf(BLUE "\nTesting dstring_trim...\n" RESET);

    // Create test data
    StringTuple test_data[] = {
        {"Hello", "Hello"},
        {" World", "World"},
        {"Programming ", "Programming"},
        {"   in  ", "in"},
        {"a      cb", "a      cb"},
        {"   ", ""},
        {" ", ""},
        {"", ""},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    // Iterate and test
    for (size_t i = 0; i < num_test_data; i++)
    {
        // Create a dstring_t
        dstring_t *s = dstring_init(test_data[i].s1);
        if (!s) return 0;

        dstring_trim(s);
        if (!str_equal(s->data, test_data[i].s2))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, test_data[i].s2);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

int test_dstring_insert()
{
    printf(BLUE "\nTesting dstring_insert...\n" RESET);

    // Define test data
    StrInsertTestData test_data[] = {
        {"Hello World", " beautiful", 4, "Hello beautiful World"},
        {"This is a test!", " cool", 8, "This is a cool test!"},
        {"Inserting", " at the end is still inserting ;)", 8, "Inserting at the end is still inserting ;)"},
        {"Just some example", "random ", 9, "Just some random example"},
        {"Here is one", " another", 6, "Here is another one"},
        {"12346789", "5", 3, "123456789"},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        StrInsertTestData datapoint = test_data[i];

        // Create the dstring_t instance
        dstring_t *s = dstring_init(datapoint.original);

        // Perform the insertion
        dstring_insert(s, datapoint.s_insert, datapoint.insert_after_idx);

        // Check the result
        if (!str_equal(datapoint.result, s->data))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, datapoint.result);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
