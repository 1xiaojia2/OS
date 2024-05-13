#include <kernel/sync.h>
#include <asm/cpu.h>
#include <kdebug.h>
#include <kernel/process/thread.h>

void sema_init(struct semaphore* psema, uint8_t value) {
   psema->value = value; 
   dlist_init(&psema->waiters);
}


void lock_init(struct lock* plock) {
   plock->holder = NULL;
   plock->holder_repeat_nr = 0;
   sema_init(&plock->semaphore, 1);
}

void sema_down(struct semaphore* psema) {
   intr_status old_status = cli();
   
   while(psema->value == 0) {
      ASSERT(!dlist_elem_find(&psema->waiters, &running_thread()->state_list_tag));

      if (dlist_elem_find(&psema->waiters, &running_thread()->state_list_tag)) {
        //TODO: PANIC
      }
      dlist_append(&psema->waiters, &running_thread()->state_list_tag); 
      thread_block(BLOCKED); 
   }
   psema->value--;
   ASSERT(psema->value == 0);	    
   cpu_set_intr_flag(old_status);
}

void sema_up(struct semaphore* psema) {

   intr_status old_status = cli();
   ASSERT(psema->value == 0);	    
   if (!dlist_is_empty(&psema->waiters)) {
      thread* thread_blocked = elem2entry(thread, state_list_tag, dlist_pop(&psema->waiters));
      thread_unblock(thread_blocked);
   }
   psema->value++;
   ASSERT(psema->value == 1);	    

   cpu_set_intr_flag(old_status);
}

void lock_acquire(struct lock* plock) {

   if (plock->holder != running_thread()) { 
      sema_down(&plock->semaphore);
      plock->holder = running_thread();
      ASSERT(plock->holder_repeat_nr == 0);
      plock->holder_repeat_nr = 1;
   } else {
      plock->holder_repeat_nr++;
   }
}

void lock_release(struct lock* plock) {
   ASSERT(plock->holder == running_thread());
   if (plock->holder_repeat_nr > 1) {
      plock->holder_repeat_nr--;
      return;
   }
   ASSERT(plock->holder_repeat_nr == 1);

   plock->holder = NULL;
   plock->holder_repeat_nr = 0;
   sema_up(&plock->semaphore);

}