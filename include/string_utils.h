#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// Return loops after STR_ERR_NO_TERMINATOR iterations and no '\0' was found
#define STR_LEN_THRESHOLD 1000000

int str_length(const char *str);

char *str_copy(char *dest, const char *src);

#endif
