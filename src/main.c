#include <kernel/tty.h>
#include <kernel/memory.h>
#include <stdio.h>
#include <asm/cpu.h>
#include <drivers/keryboard.h>
#include <drivers/timer.h>
#include <drivers/time.h>
#include <kernel/syslog.h>
#include <utils.h>
#include <string.h>


void kernel_init(uint32_t address){

    tty_init();

    printf("Now we are in virtual space.\n");

    init_keryboard();
    init_timer();
    init_memory(address);
    for (; ;){
    }
    
}
