#include <kernel/memory.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


extern pde_t page_directory[1024];
extern pte_t kernel_page_tables[256 * 1024];

uint32_t kernel_start = (uint32_t)(&_kernel_start);
uint32_t kernel_end = (uint32_t)(&_kernel_end);


static inline void invalidate(void * address){
    asm volatile("invlpg %0" : :"m"(address));
}



void init_pd(){}


void kernel_map_page(uint32_t va, uint32_t pa, uint32_t length, 
                        uint8_t pte_flag, uint8_t pde_flag){

    uint32_t from, to, map_to;
    
    // Set page tables
    from = PT_OFFSET(va) - PT_OFFSET(KERNEL_BASE);
    to = PT_OFFSET(va + length) - PT_OFFSET(KERNEL_BASE) + 1;
    map_to = PT_OFFSET(pa);
    for (size_t i = from; i < to; i++)
        if(!IS_PRES(kernel_page_tables[i]))
            kernel_page_tables[i] = (pte_t)((map_to + i) << 12) | pte_flag;
        else
            //TODO: panic
            printf("PT Have mapped\n");
    
    // Set page directory
    from = PD_OFFSET(PT_OFFSET(va)) - PD_OFFSET(PT_OFFSET(KERNEL_BASE));
    to = PD_OFFSET(PT_OFFSET(va + length)) - PD_OFFSET(PT_OFFSET(KERNEL_BASE)) + 1;
    for (size_t i = from; i < to; i++)
        if(!IS_PRES(page_directory[i]))
            page_directory[i + PD_OFFSET(PT_OFFSET(KERNEL_BASE))] = 
                (pde_t)(kernel_page_tables[i * 1024]) | pde_flag;
        else
            //TODO: panic
            printf("PD Have mapped\n");
}


void init_memory(uint32_t address){
    printf("===MEMORY_INITIALIZATION===\n");


    // Unmap identity mapped pages.
    printf("kernel start = 0x%x, kernel end = 0x%x\n", kernel_start, kernel_end);
    for (size_t i = 0; i < PD_OFFSET(PT_OFFSET(kernel_end - KERNEL_BASE)) + 1; i++)
        page_directory[i] = NOT_PRESENT;
    invalidate((unsigned *)0);

    parse_mbi(address);

    
    
    //kernel_map_page(0xFEE00000, 0xFEE00000, 0x11FFFFF, 3, 3);
    
    printf("=========MEM END============\n");

    
}

void parse_mbi(uint32_t address){
    address += KERNEL_BASE;
    struct multiboot_tag *tag;

    for (tag = (struct multiboot_tag *) (address + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                       + ((tag->size + 7) & ~7)))
    {
        printf("tag:%d\n", tag->type);
      switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
          printf ("Boot loader name = %s\n",
                  ((struct multiboot_tag_string *) tag)->string);
          break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
          printf ("mem_lower = %uKB, mem_upper = %uKB\n",
                  ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower,
                  ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper);
          break;
        case MULTIBOOT_TAG_TYPE_MMAP:
          {
            multiboot_memory_map_t *mmap;
            printf ("mmap\n");
            for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
                 (multiboot_uint8_t *) mmap 
                   < (multiboot_uint8_t *) tag + tag->size;
                 mmap = (multiboot_memory_map_t *) 
                   ((unsigned long) mmap
                    + ((struct multiboot_tag_mmap *) tag)->entry_size))
              printf (" base_addr = 0x%x%x,"
                      " length = 0x%x%x, type = 0x%x\n",
                      (unsigned) (mmap->addr >> 32),
                      (unsigned) (mmap->addr & 0xffffffff),
                      (unsigned) (mmap->len >> 32),
                      (unsigned) (mmap->len & 0xffffffff),
                      (unsigned) mmap->type);
          }
          break;
        }

    }
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