#include <kernel/memory.h>
#include <stdio.h>
#include <string.h>
#include <kernel/syslog.h>
#include <stddef.h>

extern pde_t page_directory[1024];
extern pte_t kernel_page_tables[256 * 1024];


void init_memory(unsigned address){
 
    // Unmap identity mapped pages.
    for (size_t i = 0; i < PDE_INDEX(kernel_end) + 1; i++){
        page_directory[i] = NOT_PRESENT;
    }
    flush_tlb();

    pmm_init(address);
    vmm_init();


}


/*  I have given up for managing memory by bitmap. 
void mark_as_occupied(uint32_t start_page, size_t count){
    
    if(start_page >= 0x100000 || start_page + count >= 0x100000){      
        return ;
    }    
    // Calculate the index of the page in bitmap.  
    uint32_t index = start_page / 32;
    int remainder = start_page % 32;
    unsigned int num = 1 << remainder;

    while (num < 0x80000000 && count != 0){
        bitmap[index] += num;
        num <<= 1;
        count--;
    }

    if(count == 0) return ;

    bitmap[index] += 0x80000000;
    count--;
    
    while (count != 0){
        index++;
        num = 1;
        if(count <= 31){
            bitmap[index] = (num << count) - 1;
            return ;
        }
        bitmap[index] = 0xFFFFFFFF;
        count -= 32;
    }
}
*/


// void pmm_init(){
//     stack_top = ((struct multiboot_tag_basic_meminfo *)(mbi_tag_address[MULTIBOOT_TAG_TYPE_BASIC_MEMINFO]))->mem_upper * 1024;
//     printf("[MM]: Stack range from 0x%x to 0x%x, size: 0x%x\n", stack_top - 0x100000, stack_top, 0x100000);
//     //mark_as_occupied(AT_PAGE(stack_top - STACK_SIZE), CEILING(STACK_SIZE, 0x1000));
// /*
//     int min_page = AT_PAGE(((struct multiboot_tag_basic_meminfo *)(mbi_tag_address[MULTIBOOT_TAG_TYPE_BASIC_MEMINFO]))->mem_lower * 1024);
//     int max_page = AT_PAGE((((struct multiboot_tag_basic_meminfo *)(mbi_tag_address[MULTIBOOT_TAG_TYPE_BASIC_MEMINFO]))->mem_upper + 0x1000) * 1024) - 1;
//     printf("[MM]: Min_page: %d, Max_page: %d\n", min_page, max_page);
//     mark_as_occupied(0, min_page);
//     mark_as_occupied(max_page, AT_PAGE(0xFFFFFFFF) - max_page);
// */
//     struct multiboot_tag_mmap *mmap = (struct multiboot_tag_mmap *)mbi_tag_address[MULTIBOOT_TAG_TYPE_MMAP];

//     for (multiboot_memory_map_t *mmap_entry = mmap->entries;
//         (multiboot_uint8_t *) mmap_entry 
//         < (multiboot_uint8_t *) mmap + mmap->size;
//         mmap_entry = (multiboot_memory_map_t *) 
//         ((unsigned long) mmap_entry + mmap->entry_size))      
//     {
        
//             uint32_t addr = (mmap_entry->addr) & 0xFFFFFFFF;
//             uint32_t len = (mmap_entry->len) & 0xFFFFFFFF;
//             uint32_t type = mmap_entry->type;
        
//             printf("[MM]: Memory occupied: base_address: 0x%x, length: 0x%x, type: %d\n", addr, len, type);
//             mark_as_occupied(AT_PAGE(addr), CEILING(len, 0x1000));
//         }     

// }

/*
* Let`s think how to map one page.
* For example, we want to map 0xC0000000 to 0x200000,
* what we should do is as follow:
*   1. Set some 'pde' with the first 20 bits of the 
*       address of some pafe table and flag.
*   2. Set some 'pte' with the first 20 bits of the
*       address of some physical page and flag.
*  Which pde/pte should be filled with which address?
*       For above example, the first index of 'pde' that should be filled
*  is 768(which is 0xC0000000 / 0x400000, virtual address divide by 
*  the size contained by A 'pte'). Because our page table will only map
*  the address above 3 GiB, so address of the first page table should be
*  filled in the 768th 'pde'.    
*/