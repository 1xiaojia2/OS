#include <kernel/process/thread.h>
#include <x86/headers.h>

#include <string.h>
#include <stdio.h>
#include <kdebug.h>
#include <kernel/mm/vmm.h>
#include <asm/cpu.h>
#include <stdio.h>
#include <kernel/mm/kmalloc.h>

thread *main_thread;
thread *current_thread;
static struct dlist thread_ready_list;
static struct dlist thread_all_list;


extern void switch_to(uintptr_t cur_stack, uintptr_t next_stack);
void init_thread(thread *tcb, char *tname, uint16_t priority, uintptr_t stack_base, uint32_t stack_size);
void init_thread_stack(thread *tcb, void *exec, void *args);

thread* running_thread(){ 
    return current_thread; 
}

static void kthread(void *exec_func, void *exec_args){
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
void init_thread(thread *tcb, char *tname, uint16_t priority, uintptr_t stack_base, uint32_t stack_size){

    memset(tcb, 0, sizeof(thread));
    strcpy(tcb->tname, tname);
    tcb->state = CREATED; 
    tcb->stack = stack_base;
    tcb->stack_base = stack_base;
    tcb->stack_size = stack_size;
    tcb->priority = priority;
    tcb->ticks = priority;
    tcb->total_ticks = 0;
}

void thread_push(thread *tcb){
    tcb->state = READY;
    ASSERT(!dlist_elem_find(&thread_ready_list, &tcb->state_list_tag));
    dlist_append(&thread_ready_list, &tcb->state_list_tag);
}

thread *thread_create(char *tname, uint16_t priority, void *exec, void *args){
    thread *tcb = kmalloc(sizeof(thread));
    uintptr_t thread_stack = vm_alloc_thread_block();
    thread_stack = (uintptr_t)((uint32_t)thread_stack + PAGE_SIZE);
    init_thread(tcb, tname, priority, thread_stack, PAGE_SIZE);
    init_thread_stack(tcb, exec, args);

    ASSERT(!dlist_elem_find(&thread_all_list, &tcb->all_list_tag)); 
    dlist_append(&thread_all_list, &tcb->all_list_tag);

    return tcb;
}

void init_main_thread(void) { 
    main_thread = kmalloc(sizeof(thread)); 
    init_thread(main_thread, "kernel_main", MAIN_THREAD_PRIO, BOOT_STACK_BASE, BOOT_STACK_SIZE); 
    main_thread->state = RUNNING;
    ASSERT(!dlist_elem_find(&thread_all_list, &main_thread->all_list_tag)); 
    dlist_append(&thread_all_list, &main_thread->all_list_tag); 
    current_thread = main_thread;
}

void schedule(){

    // cli();
    thread* pre_cur = current_thread;
    if (pre_cur->state == RUNNING) { 
        ASSERT(!dlist_elem_find(&thread_ready_list, &pre_cur->state_list_tag)); 
        dlist_append(&thread_ready_list, &pre_cur->state_list_tag); 
        pre_cur->ticks = pre_cur->priority; 
        pre_cur->state = READY; 
    }
    else{
        //TODO: Other state
    }
    struct dlist_elem* thread_tag = dlist_pop(&thread_ready_list);
    thread* next = elem2entry(thread, state_list_tag, thread_tag);
    next->state = RUNNING;
    current_thread = next;
    switch_to(&pre_cur->stack, &current_thread->stack); 
}

void thread_init(){
    dlist_init(&thread_all_list);
    dlist_init(&thread_ready_list);
    init_main_thread();
}


void thread_block(task_state state){
   ASSERT(((state == RUNNING) || (state == READY)));
   intr_status old_status = cli();
   thread* cur_thread = running_thread();
   cur_thread->state = state;
   schedule();	
   cpu_set_intr_flag(old_status);    
}
void thread_unblock(thread* pthread){
    ASSERT(((pthread->state == BLOCKED)));
    ASSERT(!dlist_elem_find(&thread_ready_list, &pthread->state_list_tag));
    intr_status old_status = cli();
    dlist_push(&thread_ready_list, &pthread->state_list_tag);
    pthread->state = READY;
   cpu_set_intr_flag(old_status);
}

void thread_destory(thread *pthread){
    if(pthread->state == RUNNING){

    }else if(pthread->state == READY){
        // 1. Pop it from 'ready list'.
        ASSERT(dlist_elem_find(&thread_ready_list, &pthread->state_list_tag));
        dlist_remove(&pthread->state_list_tag);
        // 2. Pop it from 'all list'.
        ASSERT(dlist_elem_find(&thread_all_list, &pthread->all_list_tag));
        dlist_remove(&pthread->all_list_tag);
        // 3. Free stack.
        size_t count = pthread->stack_size / PAGE_SIZE;
        for (size_t i = 0; i < count; i++)
            vm_free(pthread->stack_base+i*PAGE_SIZE);
        // 4. Free tcb.
        kfree(pthread);
    }
}