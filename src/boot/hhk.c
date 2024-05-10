#include <stdint.h>
#include <stddef.h>

#define KERNEL_BASE 0xC0000000
#define PT_OFFSET(address)  ((address) >> 12)
#define PD_OFFSET(page)     ((page) >> 10)

extern unsigned _kernel_start;
extern unsigned _kernel_end;

__attribute__((section(".boot.text")))
void hhk(uint32_t *page_directory, uint32_t *page_tables) {

    uint32_t kernel_start, kernel_end, from, to;
    
    kernel_start = &_kernel_start;
    kernel_end = &_kernel_end;
    kernel_end -= KERNEL_BASE;

    /* Use the same page tables. */
    from = 0;
    to = PT_OFFSET(kernel_end);
    for (size_t i = from; i <= to; i++){
        /* Each page table entry is set to present (P) and writable (W). */
        page_tables[i] = (i << 12) | 0x03;
    }

    /* Map the page_tables to the page_directory. */
    // Index of the first pde is 0
    from = 0;   
    // Index of the last pde is the pde containing the address of kernel_end.
    to = PD_OFFSET(PT_OFFSET(kernel_end)); 
    for (size_t i = from; i <= to; i++){
        page_directory[i] = (((uint32_t)(page_tables + 1024 * i))) | 0x03;
        page_directory[i + PD_OFFSET(PT_OFFSET(KERNEL_BASE))] 
            = (((uint32_t)(page_tables + 1024 * i))) | 0x03;
    }
}
/*
    C0000 000        C0202 3E3
        |               |
    00200 000        00402 3E3
1100 0000 00 | 10 0000 0010 | 0011 1110 0011
index in pd  | index in pt  | offset in page
    300      |      202     |       3E3

1100 0000 00 00 0000 0000 | 0000 0000 0000    
0000 0000 00 10 0000 0000 | 0000 0000 0000

1100 0000 00 10 0000 0010 | 0011 1110 0011

*/