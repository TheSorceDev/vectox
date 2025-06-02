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