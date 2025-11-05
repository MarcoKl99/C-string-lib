#include <stdio.h>

#include "template.h"
#include "dstring_utils.h"
#include "string_utils.h"

#include "sexyness.h"

int test_template()
{
    printf(BLUE "\nTesting template_apply...\n" RESET);

    // Define test data
    dstring_t *s1 = dstring_init("Hello {{name}}!");
    char *keys1[] = {"name"};
    char *values1[] = {"Bob"};
    size_t size1 = 1;
    char *res1 = "Hello Bob!";

    dstring_t *s2 = dstring_init("This is a {{man}} {{mod}}");
    char *keys2[] = {"man", "mod"};
    char *values2[] = {"Porsche", "GT3"};
    size_t size2 = 2;
    char *res2 = "This is a Porsche GT3";

    dstring_t *s3 = dstring_init("{{param1}}{{param2}}{{param3}}");
    char *keys3[] = {"param1", "param2", "param3"};
    char *values3[] = {"hello", "hello", "hello"};
    size_t size3 = 3;
    char *res3 = "hellohellohello";

    dstring_t *s4 = dstring_init("E-MAIL: <{{email}}>");
    char *keys4[] = {"email"};
    char *values4[] = {"test@test.com"};
    size_t size4 = 1;
    char *res4 = "E-MAIL: <test@test.com>";

    dstring_t *s5 = dstring_init("Hello my first name is {{upper:first}} and my last name is {{lower:last}}");
    char *keys5[] = {"first", "last"};
    char *values5[] = {"Bob", "Bauer"};
    size_t size5 = 2;
    char *res5 = "Hello my first name is BOB and my last name is bauer";

    dstring_t *s6 = dstring_init("This string's name is {{upper:name}} + non-literal chars {{upper:nonliteral}} {{lower:nonliteral}}");
    char *keys6[] = {"name", "nonliteral"};
    char *values6[] = {"Peter", "&/§!"};
    size_t size6 = 2;
    char *res6 = "This string's name is PETER + non-literal chars &/§! &/§!";

    DstringTemplateTestData test_data[] = {
        {s1, keys1, values1, size1, res1},
        {s2, keys2, values2, size2, res2},
        {s3, keys3, values3, size3, res3},
        {s4, keys4, values4, size4, res4},
        {s5, keys5, values5, size5, res5},
        {s6, keys6, values6, size6, res6},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        for (size_t iterator = 0; iterator < 100; iterator++)
        {
            DstringTemplateTestData td = test_data[i];

            env_t env = {td.keys, td.values, td.num_params};

            template_apply(td.s, &env);

            if (!str_equal(td.s->data, td.result))
            {
                printf(RED "\t🔴 Failed: %s != %s\n", td.s->data, td.result);
                return 0;
            }
        }
    }

    printf(GREEN "\t🟢 Passed!\n" RESET);
    return 1;
}
