#include<x86/gdt.h>
#include<x86/idt.h>
#include <string.h>

static struct gdt_entry gdt[GDT_SIZE];
static struct idt_entry idt[IDT_SIZE];

void init_gdt(){
    struct gdt_ptr_struct gdt_ptr;

    gdt_ptr.base = &gdt;
    gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_SIZE - 1;

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL0, GDT_FLAGS);
    set_gdt_entry(2, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL0, GDT_FLAGS);
    set_gdt_entry(3, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL3, GDT_FLAGS);
    set_gdt_entry(4, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL3, GDT_FLAGS);

    gdt_flush(&gdt_ptr);
}

void init_idt(){
    struct idt_ptr_struct idt_ptr;

    idt_ptr.base = &idt;
    idt_ptr.limit = sizeof(struct idt_entry) * IDT_SIZE  - 1;
    
    set_idt_entry(0, isr_stub_0, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(1, isr_stub_1, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(2, isr_stub_2, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(3, isr_stub_3, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(4, isr_stub_4, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(5, isr_stub_5, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(6, isr_stub_6, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(7, isr_stub_7, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(8, isr_stub_8, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(9, isr_stub_9, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(10, isr_stub_10, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(11, isr_stub_11, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(12, isr_stub_12, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(13, isr_stub_13, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(14, isr_stub_14, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(15, isr_stub_15, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(16, isr_stub_16, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(17, isr_stub_17, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(18, isr_stub_18, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(19, isr_stub_19, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(20, isr_stub_20, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(21, isr_stub_21, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(22, isr_stub_22, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(23, isr_stub_23, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(24, isr_stub_24, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(25, isr_stub_25, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(26, isr_stub_26, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(27, isr_stub_27, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(28, isr_stub_28, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(29, isr_stub_29, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(30, isr_stub_30, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(31, isr_stub_31, 0x08, IDT_INTR_ACCESS_DPL0);

    set_idt_entry(32, irq_stub_0, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(33, irq_stub_1, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(34, irq_stub_2, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(35, irq_stub_3, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(36, irq_stub_4, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(37, irq_stub_5, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(38, irq_stub_6, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(39, irq_stub_7, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(40, irq_stub_8, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(41, irq_stub_9, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(42, irq_stub_10, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(43, irq_stub_11, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(44, irq_stub_12, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(45, irq_stub_13, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(46, irq_stub_14, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(47, irq_stub_15, 0x08, IDT_INTR_ACCESS_DPL0);

    pic_remap();
    idt_flush(&idt_ptr);
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

void set_idt_entry(uint8_t vector, uintptr_t isr, uint16_t segment_selector, uint8_t access){
    uint32_t offset = (uint32_t)isr;

    idt[vector].offset_low = offset & 0xFFFF;
    idt[vector].offset_high = (offset >> 16) & 0xFFFF;
    
    idt[vector].segment_selector = segment_selector;
    idt[vector].zero = 0;
    idt[vector].access = access;
}
