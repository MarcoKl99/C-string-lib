#include <stdio.h>

#include "string_utils.h"

#include "string_tests.h"
#include "dstring_tests.h"
#include "template_tests.h"
#include "env_parser_tests.h"

#include "sexyness.h"
#include "report.h"


int main(int argc, char *argv[])
{
    // Print the initial banner for that WOW effect ;)
    amazing_test_intro();

    // Track the number of passed tests
    size_t num_str = 6;
    size_t num_passed_str = 0;

    size_t num_dstring = 8;
    size_t num_passed_dstring = 0;

    size_t num_env_parser = 1;
    size_t num_passed_env_parser = 0;

    size_t num_template_parser = 1;
    size_t num_passed_template_parser = 0;

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

    /////////////////////////////////////////
    // Testing the dstring Template Parser //
    /////////////////////////////////////////
    num_passed_template_parser += test_template();

    //////////////////////////////
    // Testing the env_t Parser //
    //////////////////////////////
    num_passed_env_parser += test_env_parser();

    // Print a Test-Report to the Screen
    print_report(
        num_str,
        num_passed_str,
        num_dstring,
        num_passed_dstring,
        num_env_parser,
        num_passed_env_parser,
        num_template_parser,
        num_passed_template_parser
    );

    return 0;
}
