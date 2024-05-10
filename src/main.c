#include <kernel/tty.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <kernel/mm/memory.h>
#include <drivers/keryboard.h>
#include <drivers/clock.h>

#include <drivers/time.h>
#include <stdio.h>
#include <kernel/syslog.h>

void time_str(){
    struct tm time;
    read_rtc(&time);
    printf("time: %ld\n", sys_time());
}

void kernel_init(uint32_t address){

    tty_init();

    init_gdt();
    init_idt();
    init_keryboard();
    init_clock();

    init_memory(address);
    
    add_alarm_task(time_str, 1000, re_triggerable);

    


    for(;;);
}


