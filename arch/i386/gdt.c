#include <arch/i386/gdt.h>

uint64_t _gdt[5];
uint16_t _gdt_limit = sizeof(_gdt) - 1;
uint16_t _gdt_size = 0;

void _create_gdt_descriptor(uint32_t base, uint32_t limit, uint16_t flag){

    /* check validity of value of limit */
    if(limit > _gdt_limit) {
        // TODO: kerror
    }
    
    uint64_t descriptor;
    
    descriptor = base           & 0xFF000000;
    descriptor |= (flag << 8)   & 0x00F0FF00;          
    descriptor |= limit         & 0x000F0000;
    descriptor |= (base >> 16)  & 0x000000FF;
    
    descriptor <<= 32;

    descriptor |= base << 16;
    descriptor |= limit         & 0x0000FFFF;

    _gdt[_gdt_size++] = descriptor;
}



void _gdt_init(){
    _create_gdt_descriptor(0, 0, 0);                                 /* 0x00 */
    _create_gdt_descriptor(0, 0x000FFFFF, GDT_FLAG_CODE_DPL0);       /* 0x08 */
    _create_gdt_descriptor(0, 0x000FFFFF, GDT_FLAG_DATA_DPL0);       /* 0x10 */
    _create_gdt_descriptor(0, 0x000FFFFF, GDT_FLAG_CODE_DPL3);
    _create_gdt_descriptor(0, 0x000FFFFF, GDT_FLAG_DATA_DPL3);
}
