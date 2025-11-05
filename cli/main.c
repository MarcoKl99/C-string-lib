#include <stdio.h>

#include "env_parser.h"
#include "template.h"
#include "dstring_utils.h"
#include "string_utils.h"
#include "cli_utils.h"
#include "sexyness.h"


int main(int argc, char *argv[])
{
    amazing_cli_intro();

    // Parse CLI args
    cli_args_t *args = malloc(sizeof(cli_args_t));
    if (!args) return 1;
    parse_cli_args(argc, argv, args);

    // Parse the env file
    env_t *env = load_env(args->env_path);
    if (!env)
    {
        fprintf(stderr, "Failed to load file env! (%s)\n", args->env_path);
        return 1;
    }

    // Load the template
    dstring_t *template = dstring_from_file(args->template_path);

    // Process the template + env
    template_apply(template, env);

    if (str_length(args->output_path) > 0)
    {
        // Save the result to the specified file
        dstring_to_file(template, args->output_path);
        printf("Successfully wrote result to %s\n", args->output_path);
    }
    else
    {
        // Print the result
        printf("%s\n", template->data);
    }

    // Cleanup
    for (int i = 0; i < env->count; i++)
    {
        free(env->keys[i]);
        free(env->values[i]);
    }
    free(env->keys);
    free(env->values);
    free(env);
    dstring_free(&template);

    return 0;
}
