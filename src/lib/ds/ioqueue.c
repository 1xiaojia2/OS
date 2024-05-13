#include <ds/ioqueue.h>
#include <asm/cpu.h>
#include <kdebug.h>

/* 初始化io队列ioq */
void ioqueue_init(struct ioqueue* ioq) {
   lock_init(&ioq->lock);     // 初始化io队列的锁
   ioq->producer = ioq->consumer = NULL;  // 生产者和消费者置空
   ioq->head = ioq->tail = 0; // 队列的首尾指针指向缓冲区数组第0个位置
}

/* 返回pos在缓冲区中的下一个位置值 */
static int32_t next_pos(int32_t pos) {
   return (pos + 1) % bufsize; 
}

/* 判断队列是否已满 */
bool ioq_full(struct ioqueue* ioq) {
   ASSERT(cpu_get_intr_flag() == disable);
   return next_pos(ioq->head) == ioq->tail;
}

static bool ioq_empty(struct ioqueue* ioq) {
   ASSERT(cpu_get_intr_flag() == disable);
   return ioq->head == ioq->tail;
}

static void ioq_wait(struct task_struct** waiter) {
   ASSERT(*waiter == NULL && waiter != NULL);
   *waiter = running_thread();
   thread_block(BLOCKED);
}

static void wakeup(struct task_struct** waiter) {
   ASSERT(*waiter != NULL);
   thread_unblock(*waiter); 
   *waiter = NULL;
}

char ioq_getchar(struct ioqueue* ioq) {
   ASSERT(cpu_get_intr_flag() == disable);

   while (ioq_empty(ioq)) {
      lock_acquire(&ioq->lock);	 
      ioq_wait(&ioq->consumer);
      lock_release(&ioq->lock);
   }

   char byte = ioq->buf[ioq->tail];	
   ioq->tail = next_pos(ioq->tail);	 

   if (ioq->producer != NULL) {
      wakeup(&ioq->producer);	
   }

   return byte; 
}

void ioq_putchar(struct ioqueue* ioq, char byte) {
   ASSERT(cpu_get_intr_flag() == disable);

   while (ioq_full(ioq)) {
      lock_acquire(&ioq->lock);
      ioq_wait(&ioq->producer);
      lock_release(&ioq->lock);
   }
   ioq->buf[ioq->head] = byte;  
   ioq->head = next_pos(ioq->head); 

   if (ioq->consumer != NULL) {
      wakeup(&ioq->consumer); 
   }
}