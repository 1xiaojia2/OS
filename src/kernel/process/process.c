#include <kernel/process/process.h>
#include <kernel/mm/kmalloc.h>
#include <x86/headers.h>
#include <asm/cpu.h>
#include <kernel/mm/vmm.h>
#include <kdebug.h>

void init_proc_stack(proc *process, void *start_process, void *filename);

void k_proc(void *exec_func, void *exec_args){
    sti();
    void (*exec)(void *) = exec_func;
    exec(exec_args);
}

void start_process(void* filename_) {
   void* function = filename_;
   proc* cur = current_task();
   cur->stack += sizeof(proc_ctx);
   struct isr_regs* intr_context = (struct isr_regs*)cur->stack;	 
   intr_context->edi = intr_context->esi = intr_context->ebp = intr_context->esp = 0;
   intr_context->ebx = intr_context->edx = intr_context->ecx = intr_context->eax = 0;
   intr_context->gs = 0;
   intr_context->ds = intr_context->es = intr_context->fs = UDATA_SEG;
   intr_context->eip = function;
   intr_context->cs = KCODE_SEG;
   intr_context->eflags = (EFLAGS_IOPL_0 | EFLAGS_MBS | EFLAGS_IF_1);
   intr_context->esp0 = vm_alloc(USER_STACK_BOTTOM - PAGE_SIZE, (PG_US_U | PG_RW_W | PG_P_1));
   intr_context->ss0 = UDATA_SEG; 
   asm volatile ("pushl %0\n\t "
                  "jmp soft_iret\n\t" 
                  : 
                  : "g" (intr_context) 
                  : "memory");
}

void init_proc_stack(proc *process, void *start_process, void *filename){
   process->stack -= sizeof(struct isr_regs);
   process->stack -= sizeof(thread_ctx);
   proc_ctx *ctx = (proc_ctx *)process->stack;
   ctx->eip = k_proc;
   ctx->exec_func = start_process;
   ctx->exec_args = filename;
   ctx->ebp = k_proc;
   ctx->ebp = ctx->ebx = ctx->edi = ctx->esi = 0;
}

proc* proc_create(void* filename, char* name){
   
   proc* process = kmalloc(sizeof(proc));

   uint32_t stack = (uint32_t)vm_alloc_thread_block();
   // task_init(process, name, DEFAULT_PRIO, USER_STACK_BOTTOM, USER_STACK_SIZE); 
   task_init(process, name, DEFAULT_PRIO, stack + PAGE_SIZE, PAGE_SIZE); 

   process->pgdir = vm_alloc_thread_block();
   vm_init_page_dir(process->pgdir);

   // Apply a user space page as the stack of user process.
   // Base of the user space page is fixed('USER_STACK_BOTTOM - PAGE_SIZE').
   // So initial size of stack is 0x1000. 

   // Maybe cpoy on write.


//    create_user_vaddr_bitmap(process);
   init_proc_stack(process, start_process, filename);

   vm_unmap(USER_STACK_BOTTOM - USER_STACK_SIZE);

   return process;
}

void proc_push(proc *p){
    p->state = READY;
    task_push(p);
}










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