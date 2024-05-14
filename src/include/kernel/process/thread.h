#ifndef _THREAD_H
#define _THREAD_H
#include <stdint.h>
#include <drivers/clock.h>
#include <drivers/time.h>
#include <kernel/process/header.h>
#include <kernel/header.h>
#include <ds/dlist.h>

#define BOOT_STACK_BASE (&boot_stack_bottom)
#define BOOT_STACK_SIZE 0x4000

#define MAIN_THREAD_PRIO    31

typedef struct
{
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edi, esi;
    uint32_t eip;
    uintptr_t unused;
    uintptr_t exec_func;
    uintptr_t exec_args;
} thread_ctx;

typedef struct
{
    uintptr_t stack;
    uintptr_t stack_base;
    uint32_t stack_size;
    uint16_t ticks;
    uint16_t priority;
    task_state state;
    time_t created;
    uint32_t total_ticks;
    char tname[16];
    struct dlist_elem state_list_tag;
    struct dlist_elem all_list_tag;
} thread;

// void create_thread(thread *tcb, void *exec, void *args);
// void init_thread(thread *tcb);
thread *thread_create(char *tname, uint16_t priority, void *exec, void *args);
void thread_push(thread *tcb);
void thread_destory(thread *tcb);

void thread_init();
void schedule();
thread* running_thread();

void thread_block(task_state state);
void thread_unblock(thread* pthread);
#endif