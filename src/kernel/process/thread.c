#include <kernel/process/thread.h>
#include <x86/headers.h>

#include <string.h>
#include <stdio.h>
#include <kdebug.h>
#include <kernel/mm/vmm.h>
#include <asm/cpu.h>
#include <stdio.h>
#include <kernel/mm/kmalloc.h>

extern void switch_to(uintptr_t cur_stack, uintptr_t next_stack);

void init_thread_stack(thread *tcb, void *exec, void *args);


void kthread(void *exec_func, void *exec_args){
    sti();
    void (*exec)(void *) = exec_func;
    exec(exec_args);
}

void init_thread_stack(thread *tcb, void *exec, void *args){
    // tcb->stack -= sizeof(struct isr_regs);
    tcb->stack -= sizeof(thread_ctx);
    thread_ctx *ctx = (thread_ctx *)tcb->stack;
    ctx->eip = kthread;
    ctx->exec_func = exec;
    ctx->exec_args = args;
    ctx->ebp = kthread;
    ctx->ebp = ctx->ebx = ctx->edi = ctx->esi = 0;
}

thread *thread_create(char *tname, uint16_t priority, void *exec, void *args){
    thread *tcb = kmalloc(sizeof(thread));
    // Apply a kernel page as the stack, so stack size is 0x1000.
    // Stack bottom equal 'return address' + 0x1000.
    uintptr_t thread_stack = vm_alloc_thread_block();
    thread_stack = (uintptr_t)((uint32_t)thread_stack + PAGE_SIZE);
    task_init(tcb, tname, priority, thread_stack, PAGE_SIZE);
    init_thread_stack(tcb, exec, args);

    return tcb;
}

void thread_start(thread *pthread){
    task_push(pthread);
}