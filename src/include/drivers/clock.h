#ifndef _TIME_H
#define _TIME_H 1
#include <x86/headers.h>

typedef uint32_t clock_t;

typedef enum{
    one_shot,
    re_triggerable
} alarm_type;

struct alarm_llist
{
    uintptr_t exec_task;
    clock_t time_slice;
    clock_t residual;
    alarm_type type;
    struct alarm_llist *next;
};


void init_clock();
void clock_handler(struct isr_regs *regs);

void add_alarm_task(uintptr_t exec, size_t ms, alarm_type type);
void delete_alarm_task(uintptr_t exec);
void add_task_slice(uintptr_t exec, clock_t slice);

#endif