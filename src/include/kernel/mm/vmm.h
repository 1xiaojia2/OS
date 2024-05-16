#ifndef _MM_VMM_H
#define _MM_VMM_H 1
#include <stdint.h>

typedef unsigned long pde_t;
typedef unsigned long pte_t;

extern pde_t page_directory[1024];
extern pte_t kernel_page_tables[256 * 1024];

#define KPD_ADDRESS         (&page_directory)

#define PD_VA               (0xFFFFF000)
/** PT_VA(pd_index)     (0xFFC00000 + (0x400 * pd_index))
 *  Why 0x400?
 *  Because 'pte_t' is a 4 bytes variable, you plus 0x400 to 'pte_t'
 *  is equal to plus 0x1000 to address. 
 * pte_t *pt = (pte_t *)(0xFFC00000 + 0x1000 * pd_index); 
*/
#define PT_VA(pd_index)     (0xFFC00000 + 0x1000 * (pd_index))

#define	 PG_P_1	  1	// 页表项或页目录项存在属性位
#define	 PG_P_0	  0	// 页表项或页目录项存在属性位
#define	 PG_RW_R  0	// R/W 属性位值, 读/执行
#define	 PG_RW_W  2	// R/W 属性位值, 读/写/执行
#define	 PG_US_S  0	// U/S 属性位值, 系统级
#define	 PG_US_U  4	// U/S 属性位值, 用户级

#define START_PAGE(address) ((address) >> 12)
#define END_PAGE(address)   (((address) + 4096 - 1) >> 12)

#define PTE_INDEX(address)  (((address) >> 12) & 0x3FF)
#define PDE_INDEX(address)  ((address) >> 22)
#define PT_ADDR(pde)    ((pde) & 0xFFFFF000)
#define IS_PRES(entry)  ((entry) & 1)

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
 * @brief 初始化页目录，清空用户空间映射，复制内核空间映射，设置循环映射。
 * @param page_dir 页目录地址
 * @return 无
*/
void vm_init_page_dir(void *page_dir);

#endif