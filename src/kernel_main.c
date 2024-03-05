#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>
#include <stdio.h>


void _kernel_init(){
    _init_gdt();
    _init_idt();
}


void _kernel_main(){
    terminal_initialize();
    printf("Hello!\n");
    
    __asm__("int $0x0");
    __asm__("int $0x1");

    printf("%s\n", "hello");

}