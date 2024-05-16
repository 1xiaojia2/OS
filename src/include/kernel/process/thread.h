#ifndef _THREAD_H
#define _THREAD_H
#include <stdint.h>
#include <kernel/process/header.h>


typedef task_ctx thread_ctx;

typedef task thread;

thread *thread_create(char *tname, uint16_t priority, void *exec, void *args);
void thread_start(thread *pthread);

#endif