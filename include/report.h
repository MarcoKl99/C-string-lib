#ifndef REPORT_H
#define REPORT_H

#include <stdlib.h>

void print_metrics(char *name, size_t executed, size_t passed);
void print_report(size_t num_str, size_t num_str_passed, size_t num_dstring, size_t num_dstring_passed);

#endif
