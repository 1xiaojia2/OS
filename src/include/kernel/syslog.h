#include <stdint.h>
#include <stdarg.h>


#define INFO 0
#define WARN 1
#define ERROR 2  

#define KERNEL 0
#define MEMORY 1

#define GRUB    5

void printk(int moudle_index, int level_index, const char *format, ...);
