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

    DstringTemplateTestData test_data[] = {
        {s1, keys1, values1, size1, res1},
        {s2, keys2, values2, size2, res2},
        {s3, keys3, values3, size3, res3},
        {s4, keys4, values4, size4, res4},
    };

    size_t num_test_data = sizeof(test_data) / sizeof(test_data[0]);

    for (size_t i = 0; i < num_test_data; i++)
    {
        for (size_t iterator = 0; iterator < 100; iterator++)
        {
            DstringTemplateTestData td = test_data[i];

            template_apply(td.s, td.keys, td.values, td.num_params);

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
