#include <arch/x86/interrupts/idt.h>
#include <arch/x86/interrupts/isr.h>

struct idt_entry _idt[IDT_SIZE];
struct idt_ptr_struct _idt_ptr;
extern void *isr_table[32];
extern void *isr_stub_table[32];

void _initIdt(){
    _idt_ptr.base = &_idt[0];
    _idt_ptr.limit = sizeof(_idt[0]) * IDT_SIZE - 1;

    for (int i = 0; i < 32; i++)
        _setIdtEntry(i, isr_stub_table[i], 0x08, IDT_INTR_ACCESS_DPL0);
    

    _idtFlush(&_idt_ptr);
}


void _setIdtEntry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access){
    uint32_t offset = (uint32_t)isr;

    _idt[vector].offset_low = offset & 0xFFFF;
    _idt[vector].offset_high = (offset >> 16) & 0xFFFF;
    _idt[vector].zero = 0;
    _idt[vector].segment_selector = segment_selector;
    _idt[vector].access = access;
}

void isr_handler(struct isr_regs regs){
    void (*handler)(struct isr_regs) = isr_table[regs.vector];
    handler(regs);
}
