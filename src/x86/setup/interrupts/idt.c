#include "../setup.h"
#include <stdio.h>

extern struct idt_entry idt[IDT_SIZE];
extern struct idt_ptr_struct idt_ptr;
extern void *isr_table[32];

char *interrupt_messages[32] = {
        "Divide Error",
        "Debug Exception",
        "Non-Maskable Interrupt",
        "Breakpoint Exception",
        "Overflow Exception",
        "BOUND Range Exceeded Exception",
        "Invalid Opcode Exception",
        "Device Not Available Exception",
        "Double Fault Exception",
        "Coprocessor Segment Overrun",
        "Invalid TSS Exception",
        "Segment Not Present",
        "Stack Fault Exception",
        "General Protection Exception",
        "Page Fault Exception",
        "Reserved",
        "x87 Floating-Point Exception",
        "Alignment Check Exception",
        "Machine Check Exception",
        "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
        "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
        "Reserved", "Reserved", "Reserved"
    };

void init_idt(){
    idt_ptr.base = &idt[0];
    idt_ptr.limit = sizeof(idt[0]) * IDT_SIZE - 1;

    set_idt_entry(0, _isr_stub_0, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(1, _isr_stub_1, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(2, _isr_stub_2, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(3, _isr_stub_3, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(4, _isr_stub_4, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(5, _isr_stub_5, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(6, _isr_stub_6, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(7, _isr_stub_7, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(8, _isr_stub_8, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(9, _isr_stub_9, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(10, _isr_stub_10, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(11, _isr_stub_11, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(12, _isr_stub_12, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(13, _isr_stub_13, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(14, _isr_stub_14, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(15, _isr_stub_15, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(16, _isr_stub_16, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(17, _isr_stub_17, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(18, _isr_stub_18, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(19, _isr_stub_19, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(20, _isr_stub_20, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(21, _isr_stub_21, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(22, _isr_stub_22, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(23, _isr_stub_23, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(24, _isr_stub_24, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(25, _isr_stub_25, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(26, _isr_stub_26, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(27, _isr_stub_27, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(28, _isr_stub_28, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(29, _isr_stub_29, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(30, _isr_stub_30, 0x08, IDT_INTR_ACCESS_DPL0);
    set_idt_entry(31, _isr_stub_31, 0x08, IDT_INTR_ACCESS_DPL0);
    
    __asm__("lidt (%0)": : "m"(idt_ptr): "memory");
}


void set_idt_entry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access){
    uint32_t offset = (uint32_t)isr;

    idt[vector].offset_low = offset & 0xFFFF;
    idt[vector].offset_high = (offset >> 16) & 0xFFFF;
    
    idt[vector].zero = 0;
    idt[vector].segment_selector = segment_selector;
    idt[vector].access = access;
}


void isr_handler(struct isr_regs *regs){ 
    if(regs->vector < 32){
        /*
        void (*handler)(struct isr_regs *) = isr_table[regs->vector];
        handler(regs);
        */
       printf("Error: %s\n", interrupt_messages[regs->vector]);
       while (1) {}
    }
}


void isr0(){}
void isr1(){}
void isr2(){}
void isr3(){}
void isr4(){}
void isr5(){}
void isr6(){}
void isr7(){}
void isr8(){}
void isr9(){}
void isr10(){}
void isr11(){}
void isr12(){}
void isr13(){}
void isr14(){}
void isr15(){}
void isr16(){}
void isr17(){}
void isr18(){}
void isr19(){}
void isr20(){}
void isr21(){}
void isr22(){}
void isr23(){}
void isr24(){}
void isr25(){}
void isr26(){}
void isr27(){}
void isr28(){}
void isr29(){}
void isr30(){}
void isr31(){}
