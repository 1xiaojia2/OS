#include <kernel/mm/dmm.h>
#include <kernel/mm/vmm.h>
#include <kernel/mm/pmm.h>
#include <kernel/header.h>
#include <assert.h>

void dmm_init(heap_context *heap, uint32_t page_flags){
    assert(heap->start % MALLOC_BLOCK_ALIGN == 0);
    vm_alloc(heap->start, page_flags);
    heap->brk = heap->start + PAGE_SIZE;
}

int dmm_brk(heap_context *heap, void *addr){
    return dmm_sbrk(heap, addr - heap->brk);
}

void *dmm_sbrk(heap_context *heap, size_t increment){
    
    //TODO: Ajust return value.
    assert(increment%MALLOC_BLOCK_ALIGN==0);

    uint32_t pre_brk = heap->brk;
    uint32_t current_brk = heap->brk + increment;

    if(current_brk >= heap->max_brk || current_brk < heap->brk) return NULL;

    // New brk is in the different page.
    if(PTE_INDEX(current_brk) != PTE_INDEX(heap->brk)){
        /*
            Require a new page, base address of new 
            page is 'PTE_INDEX(current_brk)'.
        */
        uint32_t flags = vm_get_page_attr(heap->start);
        if(vm_alloc(current_brk, flags) == NULL) return NULL;
    }
    heap->brk = current_brk;
    return pre_brk;
}
