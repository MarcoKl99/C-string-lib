#include <stdio.h>
#include <math.h>

#include "report.h"
#include "sexyness.h"

void print_report(size_t num_str, size_t num_str_passed, size_t num_dstring, size_t num_dstring_passed)
{
    printf(CYAN "\n\n╔════════════════════════════════════════════════════════╗\n");
    printf("║" RESET BOLD YELLOW "   🧪 Your Test Results - Brought to you by... me! 🧪   " RESET CYAN "║\n");
    printf("╚════════════════════════════════════════════════════════╝\n" RESET);

    // Calculate the scores
    float score_str = (float)num_str_passed / (float)num_str;
    float perc_str = round(score_str * 10000) / 100.0f;

    float score_dstring = (float)num_dstring_passed / (float)num_dstring;
    float perc_dstring = round(score_dstring * 10000) / 100.0f;

    printf("string utils:  %.2f%%\n", perc_str);
    printf("dstring utils: %.2f%%\n", perc_dstring);
}
