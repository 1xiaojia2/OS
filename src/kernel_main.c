#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>
#include <kernel/memory.h>
#include <kernel/paging.h>
#include <stdio.h>



void _kernel_main(unsigned long addr){
    
    _init_gdt();
    _init_idt();
    tty_init();
    _init_memory(addr);
    //_enable_paging();
    printf("dadfas");

}
    
