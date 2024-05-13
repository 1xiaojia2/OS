// #include <kernel/process/process.h>
// #include <x86/headers.h>
// #include <drivers/time.h>
// #include <kernel/mm/vmm.h>
// #include <kernel/mm/kmalloc.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <hardware/pic.h>
// #include <kdebug.h>

// pcb *proc_table[MAX_PROC];

// pcb *current_proc;

// pcb proc0;

// pcb *proc_search_state(task_state state);
// void save_proc_ctx(struct isr_regs *ctx, pcb *proc);
// void switch_to(pcb *next_task, struct isr_regs *cxt);
// void push_proc(pcb *task);

// void idel_task(){
// }

// void init_proc(){
//     // uid = 0, father = NULL(0).
//     proc0.created = sys_time();
//     proc0.state = CREATED;
//     // TODO: more defination for proc0

//     proc0.context.cs = KCODE_SEG;
//     proc0.context.ds = KDATA_SEG;
//     proc0.context.eip = idel_task;
// }

// void schedule(){
//     pcb *next = proc_search_state(READY);
//     if(current_proc != NULL) current_proc->state = READY;
//     MAGICBP;
//     current_proc = next;
//     current_proc->state = RUNNING;
//     asm("pushl %0\n\t"
//         "jmp soft_iret\n\t"
//         :
//         : "r"(&next->context)
//         : "memory");
//     pic_sendEOI(0);
// }

// pcb *proc_search_state(task_state state){
//     for (size_t i = 0; i < MAX_PROC; i++)
//     {
//         if(proc_table[i] != NULL && 
//             proc_table[i] != current_proc && 
//             proc_table[i]->state == state)
//         {
//             return proc_table[i];
//         }
//     }
//     return NULL;
// }

// void create_proc(void (*exec)()){
//     pcb *new_task = kmalloc(sizeof(pcb));
//     uint32_t ebp = (uint32_t)vm_alloc_thread_block();
    
//     new_task->context.cs = KCODE_SEG;
//     new_task->context.ds = KDATA_SEG;
//     new_task->context.eip = exec;
//     new_task->context.ebp = ebp;

//     new_task->created = sys_time();
//     new_task->state = CREATED;
//     push_proc(new_task);
// }

// void push_proc(pcb *task){
//     for (size_t i = 0; i < MAX_PROC; i++)
//     {
//         if(proc_table[i] == NULL)
//         {
//             proc_table[i] = task;
//             task->state = READY;
//             return ;
//         }
//     }
// }