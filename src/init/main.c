#include <kernel/tty.h>
#include <kernel/memory.h>
#include <stdio.h>

void kernel_init(){
    
    tty_init();
    init_memory();
}
