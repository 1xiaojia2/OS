#include <kernel/syslog.h>
#include <kernel/tty.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <utils.h>
#include <stddef.h>

#include <stdio.h>

static const char *moudle[] = {
    "(KERNEL)", "(MEMORY)", " ", " ", " ", "(GRUB)" 
};

static const char *level[] = {
    "[INFO]", "[WARN]", "[ERROR]"
};

static const uint8_t level_color[] = {0x02, 0x06, 0x04};

static char buffer[1024];
static unsigned current_length;



/**
 * [level]: (moudle) message
*/
void fprintk(char c, va_list *ap){
    char *str;
    size_t length;

    switch (c) {
        case 'c':
            {
            int c = va_arg(*ap, int);
            buffer[current_length++] = (char)c;
            }
        case 's':
            str = va_arg(*ap, char *);
            break;
        case 'd':
            str = int2str(va_arg(*ap, int));
            break;
        case 'p':   
            str = u_dec2hex((uintptr_t)va_arg(*ap, void *)); 
            break;
        case 'x':
            str = u_dec2hex(va_arg(*ap, unsigned));
            break;
        case 'u':
            str = uint2str(va_arg(*ap, unsigned));
            break;
    }
    length = strlen(str);
    memcpy(&buffer[current_length], str, length);
    current_length += length;
}


void vprintk(const char *format, va_list ap){
    while (*format != '\0')
    {
        if(*format == '%'){
            ++format;
            fprintk(*format, &ap);
        }else{
            buffer[current_length++] = *format;
        }
        format++;
    }
}

size_t prefix(int moudle_index, int level_index){
    char *ptr = buffer;
    char *levl = level[level_index];
    strcpy(ptr, levl);
    ptr += strlen(levl);
    *ptr = ' ';
    ptr += 1;
    char *mod = moudle[moudle_index];
    strcpy(ptr, mod);
    ptr += strlen(mod);
    *ptr = ' ';
    ptr +=1;

    return strlen(levl) + strlen(mod) + 2;
}

void printk(int moudle_index, int level_index, const char *format, ...){
    current_length = 0;
    uint8_t display_color = level_color[level_index];

    current_length += prefix(moudle_index, level_index);

    va_list ap;
    va_start(ap, format);
    vprintk(format, ap);
    va_end(ap);

    buffer[current_length++] = '\n';
    buffer[current_length] = '\0';
    tty_write_with_color(buffer, display_color);
}
