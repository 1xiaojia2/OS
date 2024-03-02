#include <libc/string.h>

size_t strlen(const char* str){
    size_t length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }

    return dest;
}
