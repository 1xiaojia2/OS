#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <LeeOS/kernel/tty/tty.h>


void _kernel_init(){
    _gdt_init();
    _idt_init();
}


void _kernel_main(){
    terminal_initialize();
    
    terminal_write("Hello, kernel world!\n");
    terminal_write("new line!\n");

    //__asm__("int $0");
    //terminal_write("new line!\n");
}