#include<x86/gdt.h>
#include<x86/idt.h>

static struct gdt_entry gdt[GDT_SIZE];
static struct idt_entry idt[IDT_SIZE];

extern void *intr_stub_table[32 + 16];

void setup(){
    pic_remap();

    init_gdt();
    init_idt();
}

void init_gdt(){

    struct gdt_ptr_struct gdt_ptr;

    gdt_ptr.limit = sizeof(gdt) * GDT_SIZE - 1;
    gdt_ptr.base = &gdt[0];

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL0, GDT_FLAGS);
    set_gdt_entry(2, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL0, GDT_FLAGS);
    set_gdt_entry(3, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL3, GDT_FLAGS);
    set_gdt_entry(4, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL3, GDT_FLAGS);

    gdt_flush(gdt_ptr);
}


void init_idt(){

    struct idt_ptr_struct idt_ptr;

    idt_ptr.base = &idt[0];
    idt_ptr.limit = sizeof(idt[0]) * 256 - 1;

    for (size_t i = 0; i < 32+16; i++)
        set_idt_entry(i, intr_stub_table[i], 0x08, IDT_INTR_ACCESS_DPL0);
    
    idt_flush(idt_ptr);
}

void set_gdt_entry(size_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
    gdt[index].base_low =  base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit = limit & 0xFFFF;

    gdt[index].flags = flags;
    gdt[index].flags |= (limit >> 16) & 0x0F;
    
    gdt[index].access = access;
}

void set_idt_entry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access){
    uint32_t offset = (uint32_t)isr;

    idt[vector].offset_low = offset & 0xFFFF;
    idt[vector].offset_high = (offset >> 16) & 0xFFFF;
    
    idt[vector].zero = 0;
    idt[vector].segment_selector = segment_selector;
    idt[vector].access = access;
}
