#ifndef _HEADERS_H
#define _HEADERS_H 1

#include <stddef.h>
#include <stdint.h>

#define KCODE_SEG   0X08
#define KDATA_SEG   0X10
#define UCODE_SEG   0x18
#define UDATA_SEG   0x20

struct isr_regs
{   
    uint32_t cr2;
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi;
    uint32_t ebp, esp;
    uint32_t ebx, edx, ecx, eax;
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp0;
    uint32_t ss0;
};


void irq_install_handler(size_t vector, void (*handler)(struct isr_regs *regs));
void irq_uninstall_handler(size_t vector);
void tss_update_esp(uint32_t esp0);

#endif