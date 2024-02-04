#include <arch/i386/idt.h>

uint64_t __attribute__((aligned(8))) _idt[256];
uint16_t _idt_limit = sizeof(_idt) - 1;

void _create_idt_descriptor(uint8_t index, uint32_t offset, uint16_t selector, uint16_t flag){
    uint64_t descriptor;

    descriptor = offset;
    descriptor |= flag;

    descriptor <<= 32;

    descriptor |= selector << 16;
    descriptor |= offset & 0x0000FFFF;

    _idt[index] = descriptor;
}

void _idt_init(){
    //TODO: insert gates
}