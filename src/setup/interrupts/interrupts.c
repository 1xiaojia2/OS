#include <x86/headers.h>
#include <stdio.h>
#include <hardware/pic.h>
#include <kernel/tty.h>

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

uintptr_t interrupt_table[16] ={
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

void isr_handler(struct isr_regs *regs){ 
    printf("INT %d: %s. cs: 0x%x, eip: 0x%x, error_code: 0x%x\n", regs->vector, interrupt_messages[regs->vector],
    regs->cs, regs->eip, regs->error_code); 
    for(;;); 
}

void irq_handler(struct isr_regs *regs){ 
    void (*handler)(struct isr_regs *) = interrupt_table[regs->vector - 32];
    if(handler){
        handler(regs);
    }
    pic_sendEOI(regs->vector - 32);
}

void irq_install_handler(size_t vector, void (*handler)(struct isr_regs *regs)){
    interrupt_table[vector] = handler;
}
void irq_uninstall_handler(size_t vector){
    interrupt_table[vector] = 0;
}
