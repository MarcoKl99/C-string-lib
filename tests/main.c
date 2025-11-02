#include <stdio.h>
#include "string_utils.h"
#include "test_utils.h"
#include "sexyness.h"

int main()
{
    // Print the initial banner for that WOW effect ;)
    print_banner();

    ////////////////////////////////////////
    // Testing utility functions (char *) //
    ////////////////////////////////////////
    test_str_length();
    test_str_equal();
    test_str_copy();
    test_str_find();
    test_str_count();
    test_str_split();

    /////////////////////////////////
    // Testing dstring_t functions //
    /////////////////////////////////
    test_dstring_append();
    test_dstring_reverse();
    test_dstring_to_upper();
    test_dstring_trim();
    test_dstring_insert();

    return 0;
}
