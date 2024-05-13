#include <kernel/tty.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <kernel/mm/memory.h>
#include <kernel/mm/kmalloc.h>
#include <drivers/keryboard.h>
#include <drivers/clock.h>
#include <kernel/process/process.h>
#include <kernel/process/thread.h>

#include <drivers/time.h>
#include <stdio.h>
#include <kernel/syslog.h>
#include <asm/cpu.h>

void time_str(){
    struct tm time;
    read_rtc(&time);
    printf("%d%d/%d/%d %d:%d:%d\n", time.century, time.year, time.month, time.mday, time.hour, 
        time.minute, time.second);
}

void pt1(char *str){
    while (1)
        printf("Task[1] is running.\n"); 
}
void pt2(char *str){
    while (1)
        printf("Task[2] is running.\n");
}

void kernel_init(uint32_t address){

    tty_init();

    init_gdt();
    init_idt();
    init_keryboard();
    init_clock();

    init_memory(address);
    // add_alarm_task(time_str, 1000, re_triggerable);
    
    // char *ptr = kmalloc(PAGE_SIZE * 3);
    // printf("ptr: %p\n", ptr);
    
    thread_init();
    thread_start("k_thread_b", 8, pt2, "argB ");
    thread_start("k_thread_a", 31, pt1, "argA ");
    sti();
    while (1)
    {
        printf("MAIN\n");
    }
    
    for(;;);
}


