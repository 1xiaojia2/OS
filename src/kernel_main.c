#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>
#include <kernel/memory.h>
#include <stdio.h>



void _kernel_main(unsigned long addr){
    tty_init();
    _init_gdt();  
    _init_idt();
    _init_memory(addr);
    
}
    
