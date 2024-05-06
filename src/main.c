#include <kernel/tty.h>
#include <kernel/mm/memory.h>
#include <stdio.h>
#include <drivers/keryboard.h>
#include <drivers/clock.h>
#include <drivers/time.h>


void kernel_init(uint32_t address){

    tty_init();

    printf("Now we are in virtual space.\n");

    init_keryboard();
    init_timer();
    init_memory(address);
    
    for (; ;){
    }
    
}
