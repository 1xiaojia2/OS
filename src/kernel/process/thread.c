#include <kernel/process/thread.h>
#include <x86/headers.h>

#include <string.h>
#include <stdio.h>
#include <kdebug.h>
#include <kernel/mm/vmm.h>
#include <asm/cpu.h>
#include <stdio.h>

thread* main_thread;
struct dlist thread_ready_list;
struct dlist thread_all_list;
static struct dlist_elem* thread_tag;

extern void switch_to(thread* cur, thread* next);

thread* running_thread(){ 
    uint32_t esp; 
    asm ("mov %%esp, %0" : "=g" (esp));
    return (struct task_struct*)(esp & 0xfffff000); 
}



static void kthread(void *exec_func, void *exec_args){
    sti();
    void (*exec)(void *) = exec_func;
    exec(exec_args);
}


void create_thread(thread *tcb, void *exec, void *args){
    tcb->stack -= sizeof(struct isr_regs);
    tcb->stack -= sizeof(thread_ctx);
    thread_ctx *ctx = (thread_ctx *)tcb->stack;
    ctx->eip = kthread;
    ctx->exec_func = exec;
    ctx->exec_arg = args;
    ctx->ebp = kthread;
    ctx->ebp = ctx->ebx = ctx->edi = ctx->esi = 0;
}
void init_thread(thread *tcb, char *tname, uint16_t priority, uint32_t stack_size){
    memset(tcb, 0, sizeof(thread));
    strcpy(tcb->tname, tname);
    tcb->state = READY; 
    tcb->stack_size = stack_size;
    tcb->stack = (uintptr_t)((uint32_t)tcb + stack_size);
    tcb->priority = priority;
    tcb->ticks = priority;
    tcb->total_ticks = 0;
    tcb->bondary = 0x20240512;
}

thread *thread_start(char *tname, uint16_t priority, void *exec, void *args){
    thread *tcb = vm_alloc_thread_block();
    init_thread(tcb, tname, priority, PAGE_SIZE);
    create_thread(tcb, exec, args);

    ASSERT(!dlist_elem_find(&thread_ready_list, &tcb->state_list_tag));
    dlist_append(&thread_ready_list, &tcb->state_list_tag);

    ASSERT(!dlist_elem_find(&thread_all_list, &tcb->all_list_tag)); 
    dlist_append(&thread_all_list, &tcb->all_list_tag);

    return tcb;
}

static void make_main_thread(void) { 
    main_thread = running_thread(); 
    init_thread(main_thread, "main", 31, PAGE_SIZE); 
    main_thread->state = RUNNING;
    ASSERT(!dlist_elem_find(&thread_all_list, &main_thread->all_list_tag)); 
    dlist_append(&thread_all_list, &main_thread->all_list_tag); 
}

void schedule(){
    thread* cur = running_thread();
    if (cur->state == RUNNING) { 
        ASSERT(!dlist_elem_find(&thread_ready_list, &cur->state_list_tag)); 
        dlist_append(&thread_ready_list, &cur->state_list_tag); 
        cur->ticks = cur->priority; 
        cur->state = READY; 
    }
    else{
        //TODO: Other state
    }
    thread_tag = dlist_pop(&thread_ready_list);
    thread* next = elem2entry(thread, state_list_tag, thread_tag);
    next->state = RUNNING;
    switch_to(cur, next); 
}

void thread_init(){
    dlist_init(&thread_all_list);
    dlist_init(&thread_ready_list);
    make_main_thread();
}

void thread_block(task_state state){
   ASSERT(((state == BLOCKED) || (state == READY)));
   intr_status old_status = cli();
   thread* cur_thread = running_thread();
   cur_thread->state = state;
   schedule();	
   cpu_set_intr_flag(old_status);    
}
void thread_unblock(thread* pthread){
    intr_status old_status = cli();
    ASSERT(((pthread->state == BLOCKED) || (pthread->state == READY)));
   if (pthread->state != READY) {
        ASSERT(!dlist_elem_find(&thread_ready_list, &pthread->state_list_tag));
        if (dlist_elem_find(&thread_ready_list, &pthread->state_list_tag)) {
            //TODO: 
        }
        dlist_push(&thread_ready_list, &pthread->state_list_tag);
        pthread->state = READY;
   } 
   cpu_set_intr_flag(old_status);
}