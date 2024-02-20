#include <arch/i386/isr.h>
#include <LeeOS/kernel/tty/tty.h>

void isr0(struct interrupt_frame* frame){
    __asm__("pusha");
    terminal_clear();
    terminal_write("panic!!!");

    __asm__("popa; leave; iret"); 
}