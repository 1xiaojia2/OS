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

            if(*format == 'd') {
                int num = va_arg(ap, int);

            } else if (*format == 's')
            {
                char * str = va_arg(ap, char *);
                
            }
            

        }else {
            
        }


        format++;
    }

    va_end(ap);

    return writen;
    
}