#include <stdlib.h>

#include "dtypes.h"
#include "sexyness.h"

#include "dstring_tests.h"
#include "dstring_utils.h"

#include "string_utils.h"


/////////////////////////////////
// Testing dstring_t functions //
/////////////////////////////////
int test_dstring_set()
{
    printf(BLUE "\nTesting dstring_set...\n" RESET);

    // First, test setting it to NULL
    char *init_str = "Init string";
    dstring_t *s = dstring_init(init_str);
    if (!s)
    {
        printf(RED "\t🔴 Failed: Could not init dstring with data %s" RESET, init_str);
        return 0;
    }
    dstring_set(s, NULL);
    
    // Function should not do anthing -> Check for the init string
    if (!str_equal(s->data, init_str))
    {
        printf(RED "\t🔴 Failed: %s != %s\n", s->data, init_str);
        return 0;
    }

    // Define test data
    char *test_data[] = {
        "Test",
        "",
        "Hello this is a little bit longer of a text - think about reallocation right here ;)",
        "Another simple text.",
        "Many many strings here",
        "Hello my dear friend",
        "Want some coffee? ;)",
        "Alright, this is the same case now so let's stop right here.",
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        // Set the string
        dstring_set(s, test_data[i]);

        if (!str_equal(s->data, test_data[i]))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, test_data[i]);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}

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

int test_dstring_to_lower()
{
    printf(BLUE "\nTesting dstring_to_lower...\n" RESET);

    // Define test data
    StringTuple test_data[] = {
        {"HELLO", "hello"},
        {"A liTtlE biT MIXeD", "a little bit mixed"},
        {"is already lower", "is already lower"},
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

        dstring_to_lower(s);

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

int test_dstring_replace()
{
    printf(BLUE "\nTesting dstring_insert...\n" RESET);

    // Define test data
    StringQuad test_data[] = {
        {"hello", "ll", "l", "helo"},
        {"This is a little bit longer string that we can test on!", "can", "can surely", "This is a little bit longer string that we can surely test on!"},
        {"This is a little bit longer string that we can surely test on!", "can surely", "can", "This is a little bit longer string that we can test on!"},
        {"", "", "", ""},
        {"string", NULL, "abc", "string"},
        {"string", "str", NULL, "string"},
        {"This cuts a word!", " a word", "", "This cuts!"},
        {"And another example here.", "example", "cool test-case", "And another cool test-case here."},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        StringQuad td = test_data[i];

        // Create the dstring_t instance
        dstring_t *s = dstring_init(td.s1);
        if (!s) return 0;

        // Make the replacement
        dstring_replace(s, td.s2, td.s3);

        // Check
        if (!str_equal(s->data, td.s4))
        {
            printf(RED "\t🔴 Failed: %s != %s\n", s->data, td.s4);
            return 0;
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
