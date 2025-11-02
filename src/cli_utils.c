#include "cli_utils.h"
#include "string_utils.h"

int parse_cli_args(int argc, char *argv[], cli_args_t *args)
{
    // Check if enough arguments were passed
    if (argc < 3) return -1;

    // Save paths and init output path to NULL
    args->template_path = argv[1];
    args->env_path = argv[2];
    args->output_path = NULL;

    // Check for additional flags
    for (int i = 3; i < argc; i++)
    {
        if (str_equal(argv[i], "--out") && i + 1 < argc)
        {
            args->output_path = argv[i + 1];
            i++;  // Skip net argument as it is only the output value
        }
    }

    return 0;
}
