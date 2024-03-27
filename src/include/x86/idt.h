#ifndef _IDT_H
#define _IDT_H
#include <stddef.h>
#include <stdint.h>

#define IDT_SIZE    256
#define IDT_INTR_ACCESS_DPL0 0x8E

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

void init_idt();
void set_idt_entry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access);
extern void idt_flush(struct idt_ptr_struct idt_ptr);

#endif