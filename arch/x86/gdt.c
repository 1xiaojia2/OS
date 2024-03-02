#include <arch/x86/gdt.h>

struct gdt_entry _gdt[GDT_SIZE];
struct gdt_ptr_struct _gdt_ptr;


void _initGdt(){

    _gdt_ptr.limit = sizeof(_gdt) * GDT_SIZE - 1;
    _gdt_ptr.base = &_gdt[0];

    _setGdtEntry(0, 0, 0, 0, 0);
    _setGdtEntry(1, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL0, GDT_FLAGS);
    _setGdtEntry(2, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL0, GDT_FLAGS);
    _setGdtEntry(3, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL3, GDT_FLAGS);
    _setGdtEntry(4, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL3, GDT_FLAGS);

    _gdtFlush(&_gdt_ptr);
}

void _setGdtEntry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
    _gdt[index].base_low =  base & 0xFFFF;
    _gdt[index].base_middle = (base >> 16) & 0xFF;
    _gdt[index].base_high = (base >> 24) & 0xFF;

    _gdt[index].limit = limit & 0xFFFF;

    _gdt[index].flags = flags;
    _gdt[index].flags |= (limit >> 16) & 0x0F;
    
    _gdt[index].access = access;
}
