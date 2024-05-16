#include <kernel/process/header.h>
#include <x86/headers.h>
#include <asm/cpu.h>
#include <kernel/header.h>
#include <stddef.h>
#include <kdebug.h>
#include <kernel/mm/vmm.h>
#include <kernel/sync.h>

task *__current;
task *main_thread;
static struct dlist task_ready_list;
static struct dlist task_all_list;


struct lock pid_lock;

void init_main_thread();
void proc_activate(uint32_t cur_cr3, uint32_t next_cr3);
static pid_t allocate_pid(void);

task* current_task(){
    return __current;
}

pid_t allocate_pid(void) {
   static pid_t next_pid = 0;
   lock_acquire(&pid_lock);
   next_pid++;
   lock_release(&pid_lock);
   return next_pid;
}

void init_main_thread() { 
    main_thread = kmalloc(sizeof(task)); 

    memset(main_thread, 0, sizeof(task));
    strcpy(main_thread->name, "kernel_main");
    main_thread->pid = 0;
    main_thread->state = CREATED; 
    main_thread->priority = DEFAULT_PRIO;
    main_thread->ticks = DEFAULT_PRIO;
    main_thread->total_ticks = 0;

    // Just set the pointer to somewhere, we do not care whether 
    // memory has been allocated.
    main_thread->stack = &boot_stack_bottom;
    main_thread->stack_base = &boot_stack_bottom;
    main_thread->stack_size = BOOT_STACK_SIZE;

    // Page directory should be set by wrapper function.
    main_thread->pgdir = NULL;

    ASSERT(!dlist_elem_find(&task_all_list, &main_thread->all_list_tag));
    dlist_append(&task_all_list, &main_thread->all_list_tag);

    main_thread->state = RUNNING;
    __current = main_thread;
}

void init_task_moudel(){
    // task __tmp;
    // __tmp.stack = 0;
    // __current = &__tmp;
    dlist_init(&task_all_list);
    dlist_init(&task_ready_list);
    lock_init(&pid_lock);
    init_main_thread();

}

void task_init(task *t, char *name, uint16_t priority, uintptr_t stack_base, uint32_t stack_size){
    memset(t, 0, sizeof(task));
    strcpy(t->name, name);
    t->pid = allocate_pid();
    t->state = CREATED; 
    t->priority = priority;
    t->ticks = priority;
    t->total_ticks = 0;

    // Just set the pointer to somewhere, we do not care whether 
    // memory has been allocated.
    t->stack = stack_base;
    t->stack_base = stack_base;
    t->stack_size = stack_size;

    // Page directory should be set by wrapper function.
    t->pgdir = NULL;

    ASSERT(!dlist_elem_find(&task_all_list, &t->all_list_tag));
    dlist_append(&task_all_list, &t->all_list_tag);
}

void task_push(task *t){
    t->state = READY;
    ASSERT(!dlist_elem_find(&task_ready_list, &t->state_list_tag));
    dlist_append(&task_ready_list, &t->state_list_tag);
}

void schedule(){
    
    task* pre_cur = __current;
    if (pre_cur->state == RUNNING) { 
        ASSERT(!dlist_elem_find(&task_ready_list, &pre_cur->state_list_tag)); 
        dlist_append(&task_ready_list, &pre_cur->state_list_tag); 
        pre_cur->ticks = pre_cur->priority; 
        pre_cur->state = READY; 
    }
    else{
        //TODO: Other state
    }
    struct dlist_elem* thread_tag = dlist_pop(&task_ready_list);
    task* next = elem2entry(task, state_list_tag, thread_tag);
    next->state = RUNNING;
    __current = next;

    proc_activate(pre_cur->pgdir, __current->pgdir);

    switch_to(&pre_cur->stack, &__current->stack); 
}

void task_block(){
   intr_status old_status = cli();
   task* cur_t = __current;
   cur_t->state = BLOCKED;
   schedule();	
   cpu_set_intr_flag(old_status);    
}

void task_unblock(task* t){
    ASSERT(((t->state == BLOCKED)));
    ASSERT(!dlist_elem_find(&task_ready_list, &t->state_list_tag));
    intr_status old_status = cli();
    dlist_push(&task_ready_list, &t->state_list_tag);
    t->state = READY;
    cpu_set_intr_flag(old_status);
}

void task_destory(task *t){
    if(t->state == RUNNING){
        schedule();
        task_destory(t);
    }else if(t->state == READY){
        // 1. Pop it from 'ready list'.
        ASSERT(dlist_elem_find(&task_ready_list, &t->state_list_tag));
        dlist_remove(&t->state_list_tag);
        // 2. Pop it from 'all list'.
        ASSERT(dlist_elem_find(&task_all_list, &t->all_list_tag));
        dlist_remove(&t->all_list_tag);
        // 3. Free stack.
        size_t count = t->stack_size / PAGE_SIZE;
        for (size_t i = 0; i < count; i++)
            vm_free(t->stack_base+i*PAGE_SIZE);
        // 4. Free tcb.
        kfree(t);
    }
}

void proc_activate(uint32_t cur_cr3, uint32_t next_cr3){

    uint32_t target_cr3 = (uint32_t)vm_v2p(KPD_ADDRESS);  
    if(cur_cr3 != next_cr3){
        if(next_cr3 != 0)
            target_cr3 = (uint32_t)vm_v2p(next_cr3);  
        asm volatile ("movl %0, %%cr3" : : "r" (target_cr3) : "memory");
    }
   
   if (next_cr3) {
      tss_update_esp(KERNEL_STACK_BOTTOM);
   }
}