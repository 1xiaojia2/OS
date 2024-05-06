#ifndef _MM_PMM_H
#define _MM_PMM_H 1
#include <stdint.h>

#define FREE 1
#define USED 0
#define BITMAP_GRAN     32

#define BITMAP_BYTE_INDEX(pp)   ((pp)/BITMAP_GRAN)
#define BITMAP_BIT_OFFSET(pp)   ((pp)%BITMAP_GRAN)


void pmm_init(uint32_t mem_lower, uint32_t mem_upper);
void *pm_alloc();
int pm_free(uint32_t pp);

#endif
