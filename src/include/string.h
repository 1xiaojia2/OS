#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H 1

#include <stddef.h>

size_t strlen(const char* str);

void *memcpy(void *dest, const void *src, size_t n);

void memset(void *dest, int value, size_t length);

#endif