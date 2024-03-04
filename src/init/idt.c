#include <kernel/idt.h>
#include <stdio.h>

struct idt_entry _idt[IDT_SIZE];
struct idt_ptr_struct _idt_ptr;
extern void *isr_table[32];
extern void *isr_stub_table[32];

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

void _initIdt(){
    _idt_ptr.base = &_idt[0];
    _idt_ptr.limit = sizeof(_idt[0]) * IDT_SIZE - 1;

    for (int i = 0; i < 32; i++)
        _setIdtEntry(i, isr_stub_table[i], 0x08, IDT_INTR_ACCESS_DPL0);
    

    _idtFlush(&_idt_ptr);
}


void _setIdtEntry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access){
    uint32_t offset = (uint32_t)isr;

    _idt[vector].offset_low = offset & 0xFFFF;
    _idt[vector].offset_high = (offset >> 16) & 0xFFFF;
    
    _idt[vector].zero = 0;
    _idt[vector].segment_selector = segment_selector;
    _idt[vector].access = access;
}

void isr_handler(struct isr_regs regs){ 
    printf("ERROR: int%d, %s", regs.vector, interrupt_messages[regs.vector]);
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
