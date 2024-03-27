#include <x86/headers.h>
#include <stdio.h>
#include <hardware/pic.h>

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

static void *interrupt_table[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};


void interrupt_handler(struct isr_regs *regs){ 
    if(regs->vector < 32) {
        exceptions_reserve(regs);
        return;
    }
    void (*handler)(struct isr_regs *) = interrupt_table[regs->vector - 32];
    handler(regs);
    pic_sendEOI(regs->vector - 32);
}

void irq_install_handler(size_t vector, void (*handler)(struct isr_regs *regs)){
    interrupt_table[vector] = handler;
}
void irq_uninstall_handler(size_t vector){
    interrupt_table[vector] = 0;
}

void exceptions_reserve(struct isr_regs *regs){
    printf("INT %d: %s\n", regs->vector, interrupt_messages[regs->vector]);
}