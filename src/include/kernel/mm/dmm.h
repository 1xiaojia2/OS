#ifndef _MM_DMM_H
#define _MM_DMM_H
#include <stddef.h>
#include <stdint.h>

#define MALLOC_BLOCK_ALIGN 4

typedef struct
{
    uint32_t start;
    uint32_t brk;
    uint32_t max_brk;
} heap_context;

void dmm_init(heap_context *heap, uint32_t page_flags);
int dmm_brk(heap_context *heap, void *addr);
void *dmm_sbrk(heap_context *heap, size_t increment);

#endif
