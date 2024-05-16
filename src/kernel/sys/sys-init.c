#include <stdint.h>
#include <kernel/process/header.h>
#include <x86/headers.h>
#include <drivers/console.h>
#include <string.h>
#include <kernel/sys/syscall.h>

#define syscall_nr 32 
typedef void* syscall;
syscall syscall_table[syscall_nr];

uint32_t sys_getpid(void) {
   return current_task()->pid;
}

uint32_t sys_write(char* str) {
   console_write(str);
   return strlen(str);
}

void syscall_handler(struct isr_regs *regs){
   
   
}

void syscall_init(void) {
   syscall_table[SYS_GETPID] = sys_getpid;
   syscall_table[SYS_WRITE] = sys_write;
   syscall_table[SYS_MALLOC] = 0;
   syscall_table[SYS_FREE] = 0;
}
