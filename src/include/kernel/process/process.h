#ifndef _PROCESS_H
#define _PROCESS_H
#include <kernel/process/header.h>
#include <kernel/process/thread.h>



typedef task_ctx proc_ctx;

typedef task proc;

proc *proc_create(void* filename, char* name);
void proc_push(proc *p);

#endif