#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <LeeOS/kernel/tty/tty.h>


void _kernel_init(){
    _gdt_init();
    _idt_init();
}


void _kernel_main(){
    tty_initialize();
    
    tty_put_str("Hello, kernel world!\n");
    tty_put_str("new line!\n");
    
}