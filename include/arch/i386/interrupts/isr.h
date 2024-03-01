#ifndef _ISR_H
#define _ISR_H  1

#include <stdint.h>

typedef struct __attribute__((__packed__))
{
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
} interrupt_frame;

void _init_isr_table();

void _asm_isr0();
void _asm_isr1();
void _asm_isr2();
void _asm_isr3();
void _asm_isr4();
void _asm_isr5();
void _asm_isr6();
void _asm_isr7();
void _asm_isr8();
void _asm_isr9();
void _asm_isr10();
void _asm_isr11();
void _asm_isr12();
void _asm_isr13();
void _asm_isr14();
void _asm_isr15();
void _asm_isr16();

void interrupt_handler(interrupt_frame frame);

#endif