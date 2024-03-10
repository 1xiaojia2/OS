#include "setup.h"

extern struct gdt_entry gdt[GDT_SIZE];
extern struct gdt_ptr_struct gdt_ptr;

extern void _gdt_flush(struct gdt_ptr_struct *gdt_ptr);

void init_gdt(){

    gdt_ptr.limit = sizeof(gdt) * GDT_SIZE - 1;
    gdt_ptr.base = &gdt[0];

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL0, GDT_FLAGS);
    set_gdt_entry(2, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL0, GDT_FLAGS);
    set_gdt_entry(3, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL3, GDT_FLAGS);
    set_gdt_entry(4, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL3, GDT_FLAGS);

    asm volatile (
        "lgdt %0\n\t"
        "movw $0x10, %%cx\n\t"
        "movw %%cx, %%ds\n\t"
        "movw %%cx, %%es\n\t"
        "movw %%cx, %%fs\n\t"
        "movw %%cx, %%gs\n\t"
        "movw %%cx, %%ss\n\t"
        "ljmp $0x08, $_after_lgdt\n\t"
        "_after_lgdt:\n\t"
        :
        : "m" (gdt_ptr)
        : "ecx", "memory"
    );
}

void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
    gdt[index].base_low =  base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit = limit & 0xFFFF;

    gdt[index].flags = flags;
    gdt[index].flags |= (limit >> 16) & 0x0F;
    
    gdt[index].access = access;
}
