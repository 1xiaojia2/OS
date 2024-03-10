#include <kernel/memory.h>
#include <kernel/mbi.h>
#include <stdio.h>
#include <stdint.h>

extern pde_t page_directory[1024];
extern pte_t page_tables[1024][1024];
extern uint32_t bitmap[5197];
extern uint32_t *mbi;

void init_memory(){
    
}    

