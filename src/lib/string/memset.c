#include <string.h>

void memset(void *dest, int value, size_t length){
    unsigned char *ptr = dest;
    while (length--)
        *ptr++ = (unsigned char)value;
}