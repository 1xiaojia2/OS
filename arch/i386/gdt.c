#include <arch/i386/gdt.h>

uint64_t _gdt[5];
uint32_t _gdt_limit = sizeof(_gdt) - 1;

void creat_descriptor(size_t index, uint32_t base, uint32_t limit, uint16_t flag){
    
    //TODO: check value of limit
    
    uint64_t descriptor;
    
    descriptor = base                   & 0xFF000000;
    descriptor |= ((uint32_t)flag << 8) & 0x00F0FF00;
    descriptor |= limit                 & 0x000F0000;
    
    descriptor |= (base >> 16)          & 0x000000FF;
    
    descriptor <<= 32;

    descriptor |= base << 16;
    descriptor |= limit & 0x0000FFFF;

    _gdt[index] = descriptor;
    
}

void _gdt_init(){
    creat_descriptor(0, 0, 0x000FFFFF, 0);
    creat_descriptor(1, 0, 0x000FFFFF, GDT_CODE_DPL0);
    creat_descriptor(2, 0, 0x000FFFFF, GDT_CODE_DPL3);
    creat_descriptor(3, 0, 0x000FFFFF, GDT_DATA_DPL0);
    creat_descriptor(4, 0, 0x000FFFFF, GDT_DATA_DPL3);
}