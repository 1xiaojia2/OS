#ifndef __THREAD_SYNC_H
#define __THREAD_SYNC_H
#include <ds/dlist.h>
#include <stdint.h>
#include <kernel/process/thread.h>


struct semaphore {
   uint8_t  value;
   struct dlist waiters;
};

struct lock {
   thread* holder;
   struct semaphore semaphore;
   uint32_t holder_repeat_nr;
};


void sema_init(struct semaphore* psema, uint8_t value); 
void sema_down(struct semaphore* psema);
void sema_up(struct semaphore* psema);
void lock_init(struct lock* plock);
void lock_acquire(struct lock* plock);
void lock_release(struct lock* plock);
#endif