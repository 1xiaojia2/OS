#ifndef _PROCESS_HEADER_H
#define _PROCESS_HEADER_H
#include <stdint.h>
#include <ds/dlist.h>

#define USER_STACK_BOTTOM   0x08048000
#define USER_STACK_SIZE     0x1000
#define KERNEL_STACKBOTTOM  0xC0000000
#define KERNEL_STACK_SIZE   0x1000

#define DEFAULT_PRIO 40

typedef uint32_t pid_t;

typedef enum {
    CREATED,
    READY,
    RUNNING,
    BLOCKED,
    WAIT,
    TERMINATED,
    DIED,
} task_state;

typedef struct
{
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edi, esi;
    uint32_t eip;
    uintptr_t unused;
    uintptr_t exec_func;
    uintptr_t exec_args;
} task_ctx;

typedef struct task{
    pid_t pid;
    uintptr_t stack;
    uintptr_t stack_base;
    uint32_t stack_size;
    struct task *father;
    task_state state;
    char name[16];
    uint16_t priority;
    uint16_t ticks;
    uint32_t total_ticks;
    struct dlist_elem state_list_tag;				    
    struct dlist_elem all_list_tag;
    uintptr_t pgdir;
} task;

extern task *__current;

task* current_task();
void init_task_moudel();

void task_init(task *t, char *name, uint16_t priority, uintptr_t stack_base, uint32_t stack_size);
void task_block();
void task_unblock(task* t);
void task_push(task *t);
void task_destory(task *t);

void schedule();
#endif