#ifndef _PROCESS_H
#define _PROCESS_H
// #include <stdint.h>
// #include <drivers/clock.h>
// #include <drivers/time.h>
// #include <x86/headers.h>
// #include <kernel/process/header.h>

// #define MAX_PROC   64

// typedef struct proc_ctx
// {
//     uint32_t ds;    // pushl

//     uint32_t edi, esi;
//     uint32_t ebp, esp;
//     uint32_t ebx, edx, ecx, eax; //pushal

//     uint32_t eip;
//     uint16_t cs;
//     uint32_t eflags;    // iret
// } proc_ctx;



// typedef struct proc_control_block{   
//     uint32_t uid;
//     struct proc_control_block *father;
//     struct isr_regs context;
//     time_t created;
//     clock_t time_slice;
//     task_state state;
//     int exit_code;
// } pcb;


// void init_proc();

// void schedule();

// void create_proc(void (*exec)());

#endif