#ifndef __LIB_USER_SYSCALL_H
#define __LIB_USER_SYSCALL_H
#include <stdint.h>

enum SYSCALL_NR {
   SYS_GETPID,
   SYS_WRITE,
   SYS_MALLOC,
   SYS_FREE
};

typedef enum {
   color,
} bare_call;

void barecall_color(char *);
void bare_show_time();
void bare_cls();
void bare_roll_line();
void bare_cancel_roll();

// uint32_t getpid(void);
// uint32_t write(char* str);
// void* malloc(uint32_t size);
// void free(void* ptr);
// int32_t read(void* buf, uint32_t count);

#endif