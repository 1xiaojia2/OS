#include <arch/x86/gdt.h>
#include <arch/x86/interrupts/idt.h>
#include <LeeOS/kernel/tty/tty.h>
#include <libc/stdio.h>


void _kernel_init(){
    _initGdt();
    _initIdt();
}


void _kernel_main(){
    terminal_initialize();
    printf("Hello!\n");
    
    __asm__("int $0x0");
    __asm__("int $0x1");
    __asm__("int $0x2");
    __asm__("int $0x3");
    __asm__("int $0x4");
    __asm__("int $0x5");
    printf("%s\n", "hello");

}