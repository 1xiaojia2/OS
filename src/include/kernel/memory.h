#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/mbi.h>

#define PD_VA               0xFFFFF000
#define PT_VA(pd_index)     (0xFFC00000 + (0x400 * pd_index))
/** Why 0x400?
 *  Because 'pte_t' is a 4 bytes variable, you plus 0x400 to 'pte_t'
 *  is equal to plus 0x1000 to address. 
 * pte_t *pt = (pte_t *)(0xFFC00000 + 0x1000 * pd_index); 
*/
#define STACK_SIZE 0x100000
#define KERNEL_BASE 0xC0000000
#define PAGE_SIZE   0x1000
#define BITMAP_GRAN     32
#define NOT_PRESENT 0

#define NULL ((void *)0)

#define FREE true
#define USED false

#define START_PAGE(address) ((address) >> 12)
#define END_PAGE(address)   (((address) + 4096 - 1) >> 12)

#define PTE_INDEX(address)  (((address) >> 12) & 0x3FF)
#define PDE_INDEX(address)  ((address) >> 22)
#define PT_ADDR(pde)    (pde & 0xFFFFF000)
#define IS_PRES(entry)  ((entry) & 1)


struct memory_list
{
    uintptr_t base;
    uint32_t count;
    uintptr_t next;
};

typedef struct memory_list mlist;

typedef unsigned long pde_t;
typedef unsigned long pte_t;

extern unsigned _kernel_start;
extern unsigned _kernel_end;
static const uint32_t kernel_start = (uint32_t)(&_kernel_start);
static const uint32_t kernel_end = (uint32_t)(&_kernel_end) - KERNEL_BASE;

void init_memory(unsigned address);
void parse_mbi(unsigned address);

/* PMM   Set some bits in bitmap to indicate that pages is occupied. 
        Page is one-to-one mapped with bits. */
void pmm_init(unsigned address);
void bitmap_set(uint32_t pa, bool flag);
void bitmap_set_chunk(uint32_t base, uint32_t length, bool flag);
void bitmap_set_from_to(uint32_t from, uint32_t to, bool flag);
bool bitmap_get(uint32_t pa);

void *pm_alloc();
void pm_free(void *address);
void *pm_alloc_the_page(uint32_t base);

/* PM   Distribute page for ...*/
void vmm_init();
void vm_mmap(uint32_t pa, uint32_t va, uint32_t flags);
void vm_unmap(uint32_t va, size_t count);
void vm_unmap_page( uint32_t va);
void vm_change_map(uint32_t new_pa, uint32_t va);
void *vm_get_pa(uint32_t va);

void *vm_alloc(uint32_t va, uint32_t flags, size_t count);

static inline uint32_t get_pd_addr(){
    uint32_t pd_addr;
    asm("movl %%cr3, %0\n\t"
        :"=r" (pd_addr)
        :
        : "memory");
    pd_addr &= 0xFFFFF000;
    return pd_addr;
}

static inline void set_pd_addr(uint32_t new_pd_addr){
    asm("movl %%cr3, %%eax\n\t"
        "orl $0xFFF, %%eax\n\t"
        "orl %0, %%eax\n\t"
        "movl %%eax, %%cr3\n\t"
        :
        : "m"(new_pd_addr)
        : "eax");
}

static inline void flush_tlb(){
    set_pd_addr(get_pd_addr());
}

/* Instruction "invlpg". */
static inline void invalidate(void *address){
    asm volatile("invlpg %0" : :"m"(address));
}
#endif