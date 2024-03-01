#include <arch/i386/interrupts/isr.h>
#include <LeeOS/kernel/tty/tty.h>

/* Store the address of isr */
void* isr_table[256];

void isr0(){
    terminal_clear();
    terminal_putstr("int 0");
}

void _init_isr_table() {
    isr_table[0] = isr0;
}

void interrupt_handler(interrupt_frame frame) {
    void (*handler)() = isr_table[frame.vector];
    handler();
}