#include <kernel/mm/memory.h>
#include <kernel/mm/vmm.h>
#include <kernel/mm/pmm.h>
#include <kernel/mm/dmm.h>
#include <kernel/header.h>
#include <kernel/syslog.h>
#include <string.h>
#include <stddef.h>

extern pde_t page_directory[1024];
extern pte_t kernel_page_tables[256 * 1024];

static uint32_t pre_alloc_vp;

void *vm_find_free_kp();

void vmm_init(){
    page_directory[1023] = get_current_pd_addr() | 3;
    vm_pd_init(&page_directory); 
}

void vm_pd_init(pde_t *pd){
    /* Clear user space. */
    memset(pd, 0, PDE_INDEX(KERNEL_BASE));

    //TODO: Copy kernel space mapping?

    /* Recursive mapping. */
    pd[1023] = ((pde_t)vm_v2p(pd)) | 3;
}


void *vm_alloc_thread_block(){
    size_t count = THREAD_BLOCK_SIZE >> 12;
    for (size_t i = 0; i < count; i++)
        if(vm_v2p(THREAD_BLOCK_START + (i << 12)) == NULL)
            return vm_alloc(THREAD_BLOCK_START + (i << 12), 3);
    return NULL;
}

void *vm_alloc(uint32_t va_base, uint32_t flags){
    void *pa_base = pm_alloc();
    if(pa_base == NULL){
        //TODO: Swap page?
    }
    if(vm_mmap(pa_base, va_base, flags) == 0)
        return (void *)va_base;
    return NULL;
}

void vm_free(void *va){
    vm_unmap((uint32_t)va);
}

uint32_t vm_get_page_attr(uint32_t va){
    uint32_t pd_index = PDE_INDEX(va);
    uint32_t pt_index = PTE_INDEX(va);
    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);
    if(!IS_PRES(pd[pd_index])) return 0;
    if(!IS_PRES(pt[pt_index])) return 0;
    return pt[pt_index] & 0xFFF;
}

int vm_mmap(uint32_t pa_base, uint32_t va_base, uint32_t flags){
    uint32_t pd_index = PDE_INDEX(va_base);
    uint32_t pt_index = PTE_INDEX(va_base);
    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index])){
        // Create a new PT.
        pte_t new_pt = (pte_t)pm_alloc();
        pd[pd_index] = (new_pt & ~0xFFF) | (flags & 0xFFF) | 0x01;
        
        memset(pt, 0, PAGE_SIZE);
    }

    if(IS_PRES(pt[pt_index]) && ((pt[pt_index] >> 12) != pa_base >> 12)) {
        printk(MEMORY, WARN , "va[0x%p] has been mapped to pa[0x%p].", va_base, pt[pt_index]);
        printk(MEMORY, WARN, "You wanna map it to pa[0x%p]", pa_base);
        return -1;
    }
    pt[pt_index] = (pa_base & ~0xFFF) | (flags & 0xFFF) | 0x01;
    return 0;
}

int vm_unmap(uint32_t va_base){
    uint32_t pd_index = PDE_INDEX(va_base);
    uint32_t pt_index = PTE_INDEX(va_base);
 
    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index]) || !IS_PRES(pt[pt_index])) return 1;
    pm_free(pt[pt_index] >> 12);
    pt[pt_index] = 0;
    invalidate(va_base);
    return 0;
}

void vm_change_map(uint32_t new_pa, uint32_t va){

}

void *vm_v2p(uint32_t va){
    uint32_t pd_index = PDE_INDEX(va);
    uint32_t pt_index = PTE_INDEX(va);

    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index]) || !IS_PRES(pt[pt_index])){
        // printk(MEMORY, WARN, "NO mapping for [0x%x].", va);
        return NULL;
    }

    return (void *)(PT_ADDR(pt[pt_index]) + (va & 0xFFF));
}

void *vm_get_kernel_pd(){
    return &page_directory;
}