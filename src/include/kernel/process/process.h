#ifndef _PROCESS_H
#define _PROCESS_H
#include <stdint.h>
#include <drivers/clock.h>
#include <drivers/time.h>
#include <x86/headers.h>

typedef enum{
    READY,
    RUNNING,
    BLOCKING,
    TERMINATED,
} proc_state;


struct proc_control_block{   
    uint32_t uid;
    struct proc_control_block *father;
    char name[32];
    uintptr_t pd_address;
    time_t created;
    clock_t time_slice;
    proc_state state;
    struct isr_regs context;
    int exit_code;
};
typedef struct proc_control_block PCB;

struct PCB_llist
{
    PCB proc;
    struct PCB_llist *next;
}; 
typedef struct PCB_llist pcb_list;

void init_proc();

void schedule();
void switch_to(PCB *next);

#endif