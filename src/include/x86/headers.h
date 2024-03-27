#ifndef _HEADERS_H
#define _HEADERS_H 1

#include <stddef.h>
#include <stdint.h>

struct isr_regs
{
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
};


void irq_install_handler(size_t vector, void (*handler)(struct isr_regs *regs));
void irq_uninstall_handler(size_t vector);

#endif