#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/header.h>

#define STACK_SIZE  0x100000
#define KERNEL_BASE 0xC0000000
#define KERNEL_STACK_TOP        (0xFFC00000 - STACK_SIZE)
#define THREAD_BLOCK_START  (KERNEL_END + KERNEL_BASE)
#define THREAD_BLOCK_SIZE   0x100000


void parse_mbi(unsigned address);

void init_memory(unsigned address);

#endif