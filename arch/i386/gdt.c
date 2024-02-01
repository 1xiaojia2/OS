#include <arch/i386/gdt.h>

uint64_t _gdt[5];
uint32_t _gdt_limit = sizeof(_gdt) - 1;
uint32_t _gdt_size = 0;

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag){
    
    uint64_t descriptor;
    
    descriptor = base                   & 0xFF000000;
    descriptor |= (flag & 0x0000F0FF) << 8;
    descriptor |= limit                 & 0x000F0000;
    descriptor |= (base >> 16)          & 0x000000FF;
    
    descriptor <<= 32;

    descriptor |= base << 16;
    descriptor |= limit & 0x0000FFFF;

    _gdt[_gdt_size++] = descriptor;
}



void _gdt_init(){
    create_descriptor(0, 0, 0);                                 /* 0x00 */
    create_descriptor(0, 0x000FFFFF, GDT_FLAG_CODE_DPL0);       /* 0x08 */
    create_descriptor(0, 0x000FFFFF, GDT_FLAG_DATA_DPL0);       /* 0x10 */
    create_descriptor(0, 0x000FFFFF, GDT_FLAG_CODE_DPL3);
    create_descriptor(0, 0x000FFFFF, GDT_FLAG_DATA_DPL3);
}