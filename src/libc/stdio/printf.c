#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <kernel/tty.h>

char *int2str(int num) {
    static char str[12]; 
    char *ptr = &str[sizeof(str) - 1];

    *ptr = '\0'; 

    do {
        *--ptr = '0' + (num % 10);
        num /= 10;
    } while (num != 0);

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
            str = int2str((int)va_arg(*ap, void *)); 
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


int printf(const char* restrict format, ...) {
    char buffer[1024];
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
    terminal_putstr(buffer);

    va_end(ap);
    return 0;
}
