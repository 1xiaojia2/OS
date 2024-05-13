#ifndef _MM_VMM_H
#define _MM_VMM_H 1
#include <stdint.h>

#define PD_VA               (0xFFFFF000)
/** PT_VA(pd_index)     (0xFFC00000 + (0x400 * pd_index))
 *  Why 0x400?
 *  Because 'pte_t' is a 4 bytes variable, you plus 0x400 to 'pte_t'
 *  is equal to plus 0x1000 to address. 
 * pte_t *pt = (pte_t *)(0xFFC00000 + 0x1000 * pd_index); 
*/
#define PT_VA(pd_index)     (0xFFC00000 + 0x1000 * (pd_index))

typedef unsigned long pde_t;
typedef unsigned long pte_t;

#define START_PAGE(address) ((address) >> 12)
#define END_PAGE(address)   (((address) + 4096 - 1) >> 12)

#define PTE_INDEX(address)  (((address) >> 12) & 0x3FF)
#define PDE_INDEX(address)  ((address) >> 22)
#define PT_ADDR(pde)    ((pde) & 0xFFFFF000)
#define IS_PRES(entry)  ((entry) & 1)

static inline uint32_t get_current_pd_addr(){
    uint32_t pd_addr;
    asm("movl %%cr3, %0\n\t"
        :"=r" (pd_addr)
        :
        : "memory");
    pd_addr &= 0xFFFFF000;
    return pd_addr;
}

static inline void set_current_pd_addr(uint32_t new_pd_addr){
    asm("movl %%cr3, %%eax\n\t"
        "orl $0xFFF, %%eax\n\t"
        "orl %0, %%eax\n\t"
        "movl %%eax, %%cr3\n\t"
        :
        : "m"(new_pd_addr)
        : "eax");
}

static inline void flush_tlb(){
    set_current_pd_addr(get_current_pd_addr());
}

/* Instruction "invlpg". */
static inline void invalidate(void *address){
    asm volatile("invlpg %0" : :"m"(address));
}

/* PM   Distribute page for ...*/
void vmm_init();
int vm_mmap(uint32_t pa_base, uint32_t va_base, uint32_t flags);
int vm_unmap(uint32_t va_base);
void vm_change_map(uint32_t new_pa, uint32_t va);
void *vm_v2p(uint32_t va);
void *vm_alloc(uint32_t va_base, uint32_t flags);
void vm_free(void *va);
void *vm_get_kernel_pd();

void *vm_alloc_thread_block();
uint32_t vm_get_page_attr(uint32_t va);
/**
 * @brief 初始化页目录，清空用户空间映射，设置循环映射。
 * @param pd 页目录地址
 * @return 无
*/
void vm_pd_init(pde_t *pd);

#endif