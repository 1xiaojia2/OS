#include <x86/gdt.h>
#include <x86/idt.h>
#include <kernel/mm/memory.h>
#include <kernel/mm/kmalloc.h>
#include <kernel/mm/vmm.h>
#include <kernel/process/header.h>
#include <kernel/process/thread.h>
#include <kernel/process/process.h>
#include <kernel/tty.h>
#include <kernel/syslog.h>
#include <drivers/console.h>
#include <drivers/keryboard.h>
#include <drivers/clock.h>
#include <drivers/time.h>

#include <kdebug.h>
#include <string.h>
#include <stdio.h>
#include <asm/cpu.h>
#include <kernel/sys/syscall.h>
#include <ds/ioqueue.h>
#include <exe/shell.h>


// #define THREAD_DEBUG 1
// #define PROC_DEBUG 1
// #define SHELL 1



void pt1(char *str){
    shell();
}

void thread1(char *str){
    while (1)
        printf("Thread [%s] running, tid: [%d], args: [%s]\n", current_task()->name,current_task()->pid, str);
}
void thread2(char *str){
    while (1)
        printf("Thread [%s] running, tid: [%d], args: [%s]\n", current_task()->name,current_task()->pid, str);
}

void proc1(){
    while (1)
        printf("Process [%s] is running, pid: [%d]\n", current_task()->name,current_task()->pid);
}
void proc2(){
    while (1)
        printf("Process [%s] is running, pid: [%d]\n", current_task()->name,current_task()->pid);
}

void proc3(){
    while (1)
        printf("Process [%s] is running, pid: [%d]\n", current_task()->name,current_task()->pid);
}


void kernel_init(uint32_t address){

    cli();
    tty_init();
    console_init();
    init_gdt();
    init_idt();
    init_memory(address);
    init_task_moudel();
    init_keryboard();
    init_clock();

    printf("rolling right!\n");
    printf("rolling left!\n");

    char * ptr = kmalloc(4);
    *ptr = 'a';
    // char *ptr;
    printf("ptr address: %p", ptr);
    printf("ptr address: %c", *ptr);



#ifdef THREAD_DEBUG
    thread *thread1_tcb = thread_create("A", 40, thread1, "argsA");
    thread *thread2_tcb = thread_create("B", 40, thread2, "argsB");
    thread_start(thread1_tcb);
    thread_start(thread2_tcb);
    
    while (1)
    {
        
        printf("Main thread is running!\n");
    }
#endif

#ifdef SHELL
    thread *shell = thread_create("shell", 40, pt1, "null");
    thread_start(shell);
#endif

#ifdef PROC_DEBUG
    proc *p1 = proc_create(proc1, "proc1");
    proc *p2 = proc_create(proc2, "proc2");
    proc *p3 = proc_create(proc3, "proc3");
    proc_push(p1);
    proc_push(p2);
    proc_push(p3);
#endif    
    for(;;);
}


