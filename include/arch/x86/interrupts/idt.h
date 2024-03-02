#ifndef _I386_IDT_H
#define _I386_IDT_H 1

#include <stdint.h>


struct idt_entry
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t access;
    uint16_t offset_high;

}__attribute__((packed));

struct idt_ptr_struct
{
    uint16_t limit;
    struct idt_entry *base;
}__attribute__((packed));

struct isr_regs
{
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
}__attribute__((packed));


#define IDT_SIZE       256

#define IDT_INTR_ACCESS_DPL0 0x8E

extern void _idtFlush(struct idt_ptr_struct *addr);

void _setIdtEntry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access);

void _initIdt();

extern void isr_stub_0();
extern void isr_stub_1();
extern void isr_stub_2();
extern void isr_stub_3();
extern void isr_stub_4();
extern void isr_stub_5();
extern void isr_stub_6();
extern void isr_stub_7();
extern void isr_stub_8();
extern void isr_stub_9();
extern void isr_stub_10();
extern void isr_stub_11();
extern void isr_stub_12();
extern void isr_stub_13();
extern void isr_stub_14();
extern void isr_stub_15();
extern void isr_stub_16();
extern void isr_stub_17();
extern void isr_stub_18();
extern void isr_stub_19();
extern void isr_stub_20();
extern void isr_stub_21();
extern void isr_stub_22();
extern void isr_stub_23();
extern void isr_stub_24();
extern void isr_stub_25();
extern void isr_stub_26();
extern void isr_stub_27();
extern void isr_stub_28();
extern void isr_stub_29();
extern void isr_stub_30();
extern void isr_stub_31();


#endif