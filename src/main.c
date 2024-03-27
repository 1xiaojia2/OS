#include <kernel/tty.h>
#include <kernel/memory.h>
#include <stdio.h>
#include <asm/cpu.h>
#include <drivers/keryboard.h>
#include <drivers/timer.h>


void kernel_init(uint32_t address){

    tty_init();
    init_keryboard();
    init_timer();
    init_memory(address);
    for (; ;){}
    
}
