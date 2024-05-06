#include <kernel/mm/dmm.h>
#include<kernel/mm/kmalloc.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <kernel/syslog.h>

bool block_avaliable(uint32_t header, size_t require_size);
void *block_alloc(uint32_t *header, size_t size);
void *extend_heap(size_t increment);
void set_free_block_header(uint32_t *header, size_t pre_status, size_t size);
void *coalesce(uint32_t *header);


heap_context kheap;

void kalloc_init(){
    kheap.start = KHEAP_START;
    // '- HEAD_SIZE' is for epilogue
    kheap.max_brk = KHEAP_MAX_BRK - HEAD_SIZE;
    // Allocated a physical page, brk = start.
    dmm_init(&kheap, 2);
    // Add prologue and epilogue
    uint32_t *prologue = (uint32_t *)kheap.start;
    uint32_t *epilogue = (uint32_t *)(kheap.brk - HEAD_SIZE);
    kheap.brk -= HEAD_SIZE;
    *prologue = 3+ HEAD_SIZE;
    *epilogue = 1;
    // First block.
    uint32_t *fisrt_block = (uint32_t *)(kheap.start + HEAD_SIZE);
    set_free_block_header(fisrt_block, 1, PAGE_SIZE-2*HEAD_SIZE);
}

void *kmalloc(size_t size){
    // 1. Throughout all blocks, find a suitable blcok
    // 2. If the block is too large for allocating, then split it.
    // 3. Set status as used, set 'pre_status' of the next block as used.

    size_t require_size = PAD_SIZE(size);
    uint32_t *header;
    for ( header = (uint32_t *)kheap.start; header != kheap.brk; header += ((*header & ~0x2)/4))
    {
        if(!GET_BLOCK_STATUS(*header)){
            if(block_avaliable(*header, require_size)){
                
                
                return block_alloc(header, require_size) + HEAD_SIZE;
            }
        }
    }
    // No suitable block for allocating, try to extend heap.

    if((header = extend_heap(require_size)) == NULL) return NULL;
    
    return block_alloc(header, require_size) + HEAD_SIZE;
}

void kfree(void *ptr){
    uint32_t *header = ptr - HEAD_SIZE;
    assert(*header & 1 == 1);
    *header &= 0xFFFFFFFE;
    coalesce(header);
}

void set_free_block_header(uint32_t *header_ptr, size_t pre_status, size_t size){
    assert(size%MALLOC_BLOCK_ALIGN == 0);
    // By default, status of block is freed.
    *header_ptr = size;
    *header_ptr |= pre_status << 1;

    *((uint32_t *)((uint32_t)header_ptr + size - HEAD_SIZE)) = *header_ptr;
}

void *extend_heap(size_t increment){
    uint32_t *pre_brk;
    // dmm_sbrk return pre_brk, also is the base of new free block.
    if((pre_brk = (uint32_t *)dmm_sbrk(&kheap, increment + HEAD_SIZE)) == NULL) 
        return NULL;
    // 'brk' should point to the start of epilogue.
    kheap.brk -= HEAD_SIZE;
    uint32_t *new_epilogue = (uint32_t *)(kheap.brk);
    // After extending, 'pre_status' of epilogue is always FREE.
    *new_epilogue = 1;
    uint32_t pre_status = (*pre_brk & 2) >> 1;
    set_free_block_header(pre_brk, pre_status, increment);
    return coalesce(pre_brk);
}

void *coalesce(uint32_t *header){
    // pre_statue == USED
    if((*header & 2)) return header;
    
    uint32_t current_size = *header % 0xFFFFFFFC;

    uint32_t *pre_tailer = header - 1;
    uint32_t pre_size = *pre_tailer & 0xFFFFFFFC;
    uint32_t *pre_header = header - (pre_size/4);
    // 'pre_status' of 'pre_block' must be USED.
    set_free_block_header(pre_header, 1, current_size + pre_size);
    return pre_header;
}

bool block_avaliable(uint32_t header, size_t require_size){
    uint32_t avalible_size = header & 0xFFFFFFFC;
    assert(require_size%MALLOC_BLOCK_ALIGN==0);
    /*
        Why '(2*MALLOC_BLOCK_ALIGN)'? Isn`t it 'MALLOC_BLOCK_ALIGN'?
        We need to assure that after spliting, residual payload is
        at least 'MALLOC_BLOCK_ALIGN' bytes. 
    */
    if(avalible_size == require_size) return true;
    if(avalible_size - require_size > (2*MALLOC_BLOCK_ALIGN) &&
        avalible_size > require_size) return true; 
        
    return false;
}

void *block_alloc(uint32_t *header, size_t size){
    // 1. If necessary, split the block/chunk.
    // 2. Set header.

    uint32_t avalible_size = *header & 0xFFFFFFFC;
    uint32_t *next_block = header + (size/4);
    // Current block is USED.
    *header |= 1;
    *header = size | (*header & 0x3);
    if(avalible_size == size){
        // In this case, the block is absolutly suitable, then
        // just set 'pre_status' of the next block as USED.
        *next_block |= 2;
        return (void *)header;
    }
    set_free_block_header(next_block, 1, avalible_size - size);
    return (void *)header;
}