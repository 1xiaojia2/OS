#include <kernel/tty.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <kernel/mm/memory.h>
#include <kernel/mm/kmalloc.h>
#include <drivers/keryboard.h>
#include <drivers/clock.h>
#include <kernel/process/process.h>
#include <kernel/process/thread.h>

#include <kdebug.h>
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
    init_memory(address);
    thread_init();
    init_keryboard();
    init_clock();

    // add_alarm_task(time_str, 1000, re_triggerable);
    
    thread *t1 = thread_create("A", 31, pt1, "argA ");
    thread *t2 = thread_create("B", 31, pt2, "argB ");
    thread_push(t1);
    thread_push(t2);
    // thread_destory(t1);
    // t1 = NULL;
    while (1)
    {
        printf("MAIN\n");
    }
    
    for(;;);
}


