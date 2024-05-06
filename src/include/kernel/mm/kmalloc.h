#ifndef _MM_KALLOC_H
#define _MM_KALLOC_H
#include <kernel/mm/memory.h>
#include <kernel/header.h>

#define HEAD_SIZE   4

extern unsigned _kernel_end;
#define KHEAP_MAX_BRK   KERNEL_STACK_TOP
#define KHEAP_START   (((((unsigned)&_kernel_end) + PAGE_SIZE - 1)/PAGE_SIZE) << 12)

#define GET_BLOCK_STATUS(header)             ((header) & 1)
#define USED_BLOCK(header)                   ((header) | 1)
#define FREE_BLOCK(header)                   ((header) & 0xFFFFFFFE)
#define GET_BLOCK_STZE(header)               ((header) & 0xFFFFFFFC)
#define SET_BLOCK_STZE(header, size)         do{                                 \
                                            assert(size%MALLOC_BLOCK_ALIGN==0); \
                                            *(void *)(header) |=(size);          \
                                            }while (0)

#define PRE_BLOCK_STATUS(header)            (((header) & 0x04) >> 1)
#define CURR_BLOCK_STATUS(header)           ((header) & 0x01)

#define ROUND_UP(num)       (((num)+(MALLOC_BLOCK_ALIGN)-1) & ~(MALLOC_BLOCK_ALIGN-1))
#define PAD_SIZE(size)      (ROUND_UP(size)+HEAD_SIZE)

/**
 * @brief Initial contents of heap context.
*/
void kalloc_init();

void *kmalloc(size_t size);

void kfree(void *ptr);

#endif


