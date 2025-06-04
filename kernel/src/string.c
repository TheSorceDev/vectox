// Include utils headers. - TSD
#include "string.h"

// Include STD headers. - TSD
#include <stddef.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n) { // Creating own memcpy becouse string.h is not avalible - TSD
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    size_t i = 0;
    while (i < n && src[i]) {
        dest[i] = src[i];
        i++;
    }
    if (i < n) dest[i] = '\0';
    return dest;
}

unsigned long strtoul(const char* str, char** endptr, int base) {
    unsigned long result = 0;
    int started = 0;

    while (*str == ' ' || *str == '\t') str++;

    if (base == 0) {
        if (str[0] == '0') {
            if (str[1] == 'x' || str[1] == 'X') {
                base = 16;
                str += 2;
            } else {
                base = 8;
                str += 1;
            }
        } else {
            base = 10;
        }
    }

    while (1) {
        char c = *str;
        int digit;

        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'f') digit = 10 + (c - 'a');
        else if (c >= 'A' && c <= 'F') digit = 10 + (c - 'A');
        else break;

        if (digit >= base) break;

        result = result * base + digit;
        str++;
        started = 1;
    }

    if (endptr) *endptr = (char*)(started ? str : NULL);
    return result;
}
