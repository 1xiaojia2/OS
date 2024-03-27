#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>
#include <stddef.h>
#include <kernel/mbi.h>

#define STACK_SIZE 0x100000
#define KERNEL_BASE 0xC0000000

#define NOT_PRESENT 0

#define PT_OFFSET(address)  ((address) >> 12)
#define PD_OFFSET(page)     ((page) >> 10)
#define IS_PRES(entry)  ((entry) & 1)

typedef unsigned long pde_t;
typedef unsigned long pte_t;

extern unsigned _kernel_start;
extern unsigned _kernel_end;
extern struct multiboot_tag *mbi_tag_arr[22];

void init_memory(uint32_t address);
void mark_as_occupied(uint32_t start_page, size_t count);
void parse_mbi(uint32_t address);
#endif