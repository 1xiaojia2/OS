#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>

#define PD_INDEX(addr)  (addr >> 22)
#define PT_INDEX(addr)  (addr >> 12) & 0x3FF

#define PDE_ADDR(addr)  page_directory + PD_INDEX(addr) * 4
#define PTE_ADDR(addr)  page_tables + PD_INDEX(addr) * 4096 + PT_INDEX(addr) * 4

typedef unsigned long pde_t;
typedef unsigned long pte_t;

void init_memory();

#endif