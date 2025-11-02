#include <stdio.h>
#include <math.h>

#include "report.h"
#include "sexyness.h"

void print_metrics(char *name, size_t executed, size_t passed)
{
    // Calculate the scores
    float score = (float)passed / (float)executed;
    float perc = round(score * 10000) / 100.0f;

    // Determine the color
    if (score == 1.0) printf(GREEN);
    else if (score > 0.5) printf(YELLOW);
    else printf(RED);

    // Print the metrics
    printf("Results %s utils:\n", name);
    printf("\tExecuted:     %zu\n", executed);
    printf("\tPassed:       %zu\n", passed);
    printf("\tPercentage:   %f\n\n", perc);

    // Reset the color
    printf(RESET);
}

void print_report(
    size_t num_str,
    size_t num_str_passed,
    size_t num_dstring,
    size_t num_dstring_passed,
    size_t num_env_parser,
    size_t num_env_parser_passed,
    size_t num_template_parser,
    size_t num_template_parser_passed
)
{
    printf(CYAN "\n\n╔════════════════════════════════════════════════════════╗\n");
    printf("║" RESET BOLD YELLOW "   🧪 Your Test Results - Brought to you by... me! 🧪   " RESET CYAN "║\n");
    printf("╚════════════════════════════════════════════════════════╝\n" RESET);

    print_metrics("string", num_str, num_str_passed);
    print_metrics("dstring", num_dstring, num_dstring_passed);
    print_metrics("env_parser", num_env_parser, num_env_parser_passed);
    print_metrics("template_parser", num_template_parser, num_template_parser_passed);
}
