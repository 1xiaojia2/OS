#ifndef _THREAD_H
#define _THREAD_H
#include <stdint.h>
#include <drivers/clock.h>
#include <drivers/time.h>
#include <kernel/process/header.h>
#include <kernel/header.h>
#include <ds/dlist.h>

#define MAIN_THREAD_TCB (&boot_stack_bottom)
#define BOOT_STACK_SIZE 0x4000

typedef struct
{
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edi, esi;
    void (*eip)(void *exec, void *args);
    uintptr_t exec_returned;
    uintptr_t exec_func;
    uintptr_t exec_arg;
} thread_ctx;

typedef struct
{
    uintptr_t stack;
    uint32_t stack_size;
    task_state state;
    uint16_t ticks;
    uint16_t priority;
    time_t created;
    uint32_t total_ticks;
    char tname[16];
    struct dlist_elem state_list_tag;
    struct dlist_elem all_list_tag;
    uint32_t bondary;
} thread;

// void create_thread(thread *tcb, void *exec, void *args);
// void init_thread(thread *tcb);
thread *thread_start(char *tname, uint16_t priority, void *exec, void *args);
void thread_init();
void schedule();
thread* running_thread();
#endif