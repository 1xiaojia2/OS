#include <arch/i386/gdt.h>
#include <arch/i386/interrupts/idt.h>
#include <LeeOS/kernel/tty/tty.h>
#include <libc/stdio.h>


void _kernel_init(){
    _gdt_init();
    _idt_init();
}


void _kernel_main(){
    terminal_initialize();
    
    printf("Hello, kernel world!\n");
    printf("new line!\n");

    __asm__("int $0");
    printf("new line!\n");
}