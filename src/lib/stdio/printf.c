#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <kernel/tty.h>

char *int2str(int num) {
    char str[32]; 
    memset(str, 0, 32);
    char *ptr = &str[sizeof(str) - 1];

    *ptr = '\0'; 

    do {
        *--ptr = '0' + (num % 10);
        num /= 10;
    } while (num != 0);

    return ptr;
}

char *dec2hex(int num) {
    unsigned int n = num;
    char str[32]; 
    memset(str, 0, 32);
    char *ptr = &str[sizeof(str) - 1];

    *ptr = '\0'; 

    do {
        int remainder = n % 16;
        *--ptr = remainder < 10 ?  '0' + remainder : 'a' + (remainder - 10);
        n /= 16;
    } while (n != 0);
    return ptr;
}

int va_print(char *buffer, const char *format, int *n, va_list *ap) {
    char *str;
    size_t length;

    switch (*format) {
        case 'c':
            {
                int c = va_arg(*ap, int);

                if (*n < 1023) {
                    buffer[(*n)++] = (char)c;
                    return 0;
                } else 
                    return -1;
            }
        case 's':
            str = va_arg(*ap, char *);
            break;
        case 'd':
            str = int2str(va_arg(*ap, int));
            break;
        case 'p':   
            str = dec2hex((unsigned int)va_arg(*ap, void *)); 
            break;
        case 'x':
            str = dec2hex(va_arg(*ap, int));
            break;
        case 'u':
            str = int2str((unsigned int)va_arg(*ap, int));
            break;
        default:
            return -1;
    }
    length = strlen(str);

    if (*n + length >= 1023) return -1;

    memcpy(buffer + *n, str, length);
    *n += length;

    return 0;
}


int printf(const char* format, ...) {
    static char buffer[1024];
    va_list ap;
    va_start(ap, format);
    int n = 0;

    while (*format != '\0' && n < 1023) {
        while (*format != '%' && *format != '\0' && n < 1023) {
            buffer[n++] = *format++;
        }

        if (*format == '%') {
            format++;
            if (va_print(buffer, format++, &n, &ap) == -1)
                return -1;
        }
    }

    if (n >= 1023) return -1;

    buffer[n] = '\0';
    tty_write(buffer);

    va_end(ap);
    return 0;
}
