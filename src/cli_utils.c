#include "cli_utils.h"
#include "string_utils.h"
#include "dtypes.h"

int parse_cli_args(int argc, char *argv[], cli_args_t *args)
{
    // Check for NULLs
    if (!argv || !args) return -1;

    // Check if enough arguments were passed
    if (argc < 3) return -1;

    // Save paths and init output path to NULL
    str_copy(argv[1], args->template_path, MAX_CLI_ARG_LENGTH);
    str_copy(argv[2], args->env_path, MAX_CLI_ARG_LENGTH);

    // Check for additional flags
    for (int i = 3; i < argc; i++)
    {
        if (str_equal(argv[i], "--out") && i + 1 < argc)
        {
            str_copy(argv[i + 1], args->output_path, MAX_CLI_ARG_LENGTH);
            i++;  // Skip next argument as it is only the output value
        }
    }

    return 0;
}
