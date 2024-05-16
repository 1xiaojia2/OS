#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H 1

#include <stddef.h>

size_t strlen(const char* str);

int strcmp(const char *str1, const char *str2);

void *memcpy(void *dest, const void *src, size_t n);

void memset(void *dest, int value, size_t length);

char *strcpy(char *dest, const char *src);

void* memmove(void* dstptr, const void* srcptr, size_t size);

#endif