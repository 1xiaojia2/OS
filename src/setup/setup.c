#include<x86/gdt.h>
#include<x86/idt.h>
#include <string.h>
#include <x86/tss.h>

static struct gdt_entry gdt[GDT_SIZE];
static struct idt_entry idt[IDT_SIZE];

extern void *intr_stub_table[256];

static struct gdt_ptr_struct gdt_ptr;
static struct idt_ptr_struct idt_ptr;
static struct tss_entry_struct tss_entry;

void init_gdt(){
    gdt_ptr.base = &gdt;
    gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_SIZE - 1;

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL0, GDT_FLAGS);
    set_gdt_entry(2, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL0, GDT_FLAGS);
    set_gdt_entry(3, 0, 0x000FFFFF, GDT_ACCESS_CODE_DPL3, GDT_FLAGS);
    set_gdt_entry(4, 0, 0x000FFFFF, GDT_ACCESS_DATA_DPL3, GDT_FLAGS);
    init_tss(5, 0x10, 0);

    gdt_flush(&gdt_ptr);
    tss_flush();
}

void init_idt(){
    idt_ptr.base = &idt;
    idt_ptr.limit = sizeof(struct idt_entry) * IDT_SIZE  - 1;
    
    set_idt_entry(0, intr_stub_0, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(1, intr_stub_1, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(2, intr_stub_2, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(3, intr_stub_3, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(4, intr_stub_4, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(5, intr_stub_5, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(6, intr_stub_6, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(7, intr_stub_7, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(8, intr_stub_8, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(9, intr_stub_9, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(10, intr_stub_10, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(11, intr_stub_11, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(12, intr_stub_12, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(13, intr_stub_13, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(14, intr_stub_14, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(15, intr_stub_15, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(16, intr_stub_16, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(17, intr_stub_17, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(18, intr_stub_18, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(19, intr_stub_19, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(20, intr_stub_20, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(21, intr_stub_21, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(22, intr_stub_22, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(23, intr_stub_23, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(24, intr_stub_24, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(25, intr_stub_25, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(26, intr_stub_26, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(27, intr_stub_27, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(28, intr_stub_28, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(29, intr_stub_29, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(30, intr_stub_30, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(31, intr_stub_31, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(32, intr_stub_32, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(33, intr_stub_33, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(34, intr_stub_34, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(35, intr_stub_35, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(36, intr_stub_36, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(37, intr_stub_37, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(38, intr_stub_38, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(39, intr_stub_39, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(40, intr_stub_40, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(41, intr_stub_41, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(42, intr_stub_42, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(43, intr_stub_43, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(44, intr_stub_44, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(45, intr_stub_45, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(46, intr_stub_46, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(47, intr_stub_47, 0x08, IDT_INTR_ACCESS_DPL0);

    pic_remap();
    idt_flush(&idt_ptr);
}

void init_tss(uint32_t num, uint16_t ss0, uint32_t esp0){
    uint32_t base = (uint32_t) &tss_entry;
    uint32_t limit = base + sizeof(tss_entry);

    set_gdt_entry(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;

    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
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
