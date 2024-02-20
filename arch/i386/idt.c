#include <arch/i386/idt.h>
#include <arch/i386/isr.h>

uint64_t __attribute__((aligned(0x10))) _idt[256];
uint16_t _idt_limit = sizeof(_idt) - 1;

void _set_idt_gate(uint8_t vector, void *isr, uint16_t selector, uint16_t flag){
    
    uint32_t offset = (uint32_t)isr;
    uint64_t gate;

    gate = offset             & 0xFFFF0000;
    gate |= flag              & 0x0000FFFF;

    gate <<= 32;

    gate |= selector << 16    & 0xFFFF0000;
    gate |= offset            & 0x0000FFFF;

    _idt[vector] = gate;
}

void _idt_init(){
    //TODO: insert gates
    _set_idt_gate(0, isr0, 0x08, IDT_INT_GATE_FLAG(1, 0));
    
}
