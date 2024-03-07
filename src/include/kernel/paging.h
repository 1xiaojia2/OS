#ifndef _PAGING_H
#define _PAGING_H
#include <stdint.h>

void _enable_paging();

extern void _paging_fulsh(unsigned long addr);
 
#endif