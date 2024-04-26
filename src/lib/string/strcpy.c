#include <string.h>

char *strcpy(char *dest, const char *src){
    char *ptr = dest;
    size_t index = 0;
    while (src[index] != '\0')
        *ptr++ = src[index++];
    *ptr = '\0';
    return dest;
}