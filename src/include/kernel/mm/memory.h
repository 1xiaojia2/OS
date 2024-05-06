#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define STACK_SIZE  0x100000
#define KERNEL_BASE 0xC0000000
#define KERNEL_STACK_TOP        (0xFFC00000 - STACK_SIZE)


void parse_mbi(unsigned address);

void init_memory(unsigned address);

#endif