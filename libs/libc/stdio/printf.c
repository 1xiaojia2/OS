#include <libc/stdio.h>
#include <LeeOS/kernel/tty/tty.h>

int printf(const char* restrict format, ...) {

    int writen = 0;

    va_list ap;
    va_start(ap, format);
    
    while (*format != '\0')
    {
        if(*format == '%'){
            format++;

            if(*format == 'c') {
                char c = (char)va_arg(ap, int);
                terminal_putchar(c);

            } else if (*format == 's')
            {
                char * str = va_arg(ap, char *);
                terminal_putstr(str);
            }
    
        }else {
            terminal_putchar(format[0]);
        }
        format++;
    }

    va_end(ap);

    return writen;
    
}