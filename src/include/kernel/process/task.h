#ifndef _TASK_H
#define _TASK_H
#include <stdint.h>

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} task_context;

typedef struct thread{
    task_context context;
    struct thread *next;
} TCB;


void createTask(TCB* task, void(*)(), uint32_t, uint32_t*);


#endif