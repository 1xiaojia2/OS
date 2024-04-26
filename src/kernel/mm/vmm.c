#include <kernel/memory.h>
#include <kernel/syslog.h>
#include <string.h>

extern pde_t page_directory[1024];
extern pte_t kernel_page_tables[256 * 1024];

void vmm_test(){
    char *ptr = vm_alloc(0x1000, 6, 2);
    strcpy(ptr, "hello, World!");
    printk(MEMORY, INFO, "ptr: %s", ptr);
    printk(MEMORY, INFO, "va [%x] -> pa [%x]", ptr, vm_get_pa(ptr));
    vm_unmap(0x2000, 1);
}

void vmm_init(){
    // Recursive mapping
    page_directory[1023] = get_pd_addr() | 7;
    
    vmm_test();
}

void page_dir_init(pde_t *pd, uint32_t flags){

    pd[1023] = ((pde_t)pd) | (flags & 0xFFF) | 0x01;



}

void *vm_alloc(uint32_t va, uint32_t flags, size_t count){
    for (size_t i = 0; i < count; i++)
    {
        uint32_t pa = (uint32_t)pm_alloc();
        vm_mmap(pa, va+i*PAGE_SIZE, flags);
    }
    return ((void *)(va & ~0xFFF));
}


void vm_mmap(uint32_t pa, uint32_t va, uint32_t flags){
    uint32_t pd_index = PDE_INDEX(va);
    uint32_t pt_index = PTE_INDEX(va);
 
    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index])){
        // Create a new PT.
        pte_t new_pt = (pte_t)pm_alloc();
        pd[pd_index] = (new_pt & ~0xFFF) | (flags & 0xFFF) | 0x01;
        memset(pt, 0, PAGE_SIZE);
    }

    if(IS_PRES(pt[pt_index])){
        printk(MEMORY, WARN, "There has been a mapping for va[0x%x].", va);
        return ;
    }
    pt[pt_index] = (pa & ~0xFFF) | (flags & 0xFFF) | 0x01;
}

void vm_unmap(uint32_t va, size_t count){
    for (size_t i = 0; i < count; i++)
        vm_unmap_page(va+i*PAGE_SIZE);
}

void vm_unmap_page(uint32_t va){
    uint32_t pd_index = PDE_INDEX(va);
    uint32_t pt_index = PTE_INDEX(va);
 
    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index]) || !IS_PRES(pt[pt_index])){
        printk(MEMORY, WARN, "NO mapping for va[0x%x].", va);
        return ;
    }

    pm_free((void *)pt[pt_index]);
    pt[pt_index] = 0;
    invalidate(va);
}

void vm_change_map(uint32_t new_pa, uint32_t va){

}

void *vm_get_pa(uint32_t va){
    uint32_t pd_index = PDE_INDEX(va);
    uint32_t pt_index = PTE_INDEX(va);

    pde_t *pd = PD_VA;
    pte_t *pt = PT_VA(pd_index);

    if(!IS_PRES(pd[pd_index]) || !IS_PRES(pt[pt_index])){
        printk(MEMORY, WARN, "NO mapping for [0x%x].", va);
        return NULL;
    }

    return (void *)(PT_ADDR(pt[pt_index]) + (va & 0xFFF));
}
