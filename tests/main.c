#include <stdio.h>

#include "string_utils.h"
#include "string_tests.h"
#include "dstring_tests.h"

// DEV
#include "dstring_utils.h"
#include "dstring_template.h"

#include "sexyness.h"
#include "report.h"


int main()
{
    // Print the initial banner for that WOW effect ;)
    amazing_intro();

    // Track the number of passed tests
    size_t num_str = 6;
    size_t num_passed_str = 0;

    size_t num_dstring = 9;
    size_t num_passed_dstring = 0;

    ////////////////////////////////////////
    // Testing utility functions (char *) //
    ////////////////////////////////////////
    num_passed_str += test_str_length();
    num_passed_str += test_str_equal();
    num_passed_str += test_str_copy();
    num_passed_str += test_str_find();
    num_passed_str += test_str_count();
    num_passed_str += test_str_split();

    /////////////////////////////////
    // Testing dstring_t functions //
    /////////////////////////////////
    num_passed_dstring += test_dstring_append();
    num_passed_dstring += test_dstring_reverse();
    num_passed_dstring += test_dstring_to_upper();
    num_passed_dstring += test_dstring_to_lower();
    num_passed_dstring += test_dstring_trim();
    num_passed_dstring += test_dstring_insert();
    num_passed_dstring += test_dstring_replace();
    num_passed_dstring += test_dstring_set();
    num_passed_dstring += test_dstring_template();

    print_report(num_str, num_passed_str, num_dstring, num_passed_dstring);

    return 0;
}
