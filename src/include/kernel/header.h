#ifndef _KERNEL_HEADER_H
#define _KERNEL_HEADER_H 1

#define KERNEL_BASE 0xC0000000
#define PAGE_SIZE   0x1000
#define CLOCK_PER_SEC   100
#define TIME_SLICE_MS  10
#define TIMEZONE    (8)

#define KERNEL_STACK_SIZE       (0x100000)
#define KERNEL_STACK_BOTTOM     (0xFFC00000)

#define BOOT_STACK_SIZE 0x4000

extern unsigned _kernel_end;
extern unsigned _kernel_start;
extern unsigned boot_stack_bottom;
extern unsigned boot_stack_top;

#define KERNEL_END  ((unsigned)&_kernel_end - KERNEL_BASE)
#define _kernel_start ((unsigned)&_kernel_start)

#endif