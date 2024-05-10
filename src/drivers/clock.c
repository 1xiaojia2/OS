#include<stdint.h>
#include<hardware/pit.h>
#include<kernel/header.h>
#include<drivers/clock.h>
#include <kernel/mm/kmalloc.h>
#include <stdio.h>

clock_t ticks;

typedef struct alarm_llist task_list;

static task_list task_list_head;
static task_list *task_list_last;

void clock_handler(struct isr_regs *regs){
    ticks++;
    task_list *task = task_list_head.next;
    while (task != NULL)
    {
        task->residual--;
        if(task->residual == 0){
            void (*exec)() = task->exec_task;
            exec();
            switch (task->type)
            {
            case re_triggerable:
                task->residual = task->time_slice;
                break;
            case one_shot:
                delete_alarm_task(task);
            } 
        }
        task = task->next;
    }
}

void init_clock(){
    ticks = 0;
    task_list_last = &task_list_head;
    task_list_head.next = NULL;

    irq_install_handler(0,clock_handler);
    
    uint32_t divisor = PIT_OSCILLATOR/CLOCK_PER_SEC;
    
    write_pit_count(CONTROL_WORD_REG(SC_0, 3, 2, 0), counter0, divisor);
}

void add_alarm_task(uintptr_t exec, size_t ms, alarm_type type){
    task_list *new_task = (task_list *)kmalloc(sizeof(task_list));

    new_task->exec_task = exec;
    new_task->time_slice = ms/TIME_SLICE_MS;
    new_task->residual = new_task->time_slice;
    new_task->type = type;
    new_task->next = NULL;
    task_list_last->next = new_task;
    task_list_last = new_task;
}

void delete_alarm_task(uintptr_t exec){
    if(exec == NULL) return ;
    task_list *task = task_list_head.next;
    task_list *pre_task = &task_list_head;
    while (task != NULL)
    {
        if(task->exec_task == exec){
            task_list *delete_task = task;
            pre_task->next = delete_task->next;
            kfree(delete_task);
            return ;
        }
        pre_task = task;
        task = task->next;
    }
}
void add_task_slice(uintptr_t exec, clock_t slice){
    if(exec == NULL) return NULL;
    task_list *task = task_list_head.next;
    while (task != NULL)
    {
        if(task->exec_task == exec){
            task->time_slice = slice;
            task->residual = slice;        
            return;
        }
        task = task->next;
    }
}
