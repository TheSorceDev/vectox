#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n);
char *strncpy(char* dest, const char* src, size_t n);
unsigned long strtoul(const char* str, char** endptr, int base);

#endif