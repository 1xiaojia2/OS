#ifndef _PAGING_H
#define _PAGING_H

#define PAGE_ADDRESS(addr)                          (addr << 12)
#define PAGE_LEVEL_WRITE_THROUGH(x)                 (x << 3)
#define PAGE_LEVEL_CACHE_DIS(x)                     (x << 4)
#define PAGING_CR3(address, pwt, pcd)               PAGE_ADDRESS(address) | \
                                                    PAGE_LEVEL_WRITE_THROUGH(pwd) | \
                                                    PAGE_LEVEL_CACHE_DIS(pcd) | \
                                                    0x00000000

#define PDE_RW(x)                                   (x << 1)
#define PDE_US(x)                                   (x << 2)
#define PDE_ACCESSED(x)                             (x << 5)
#define PDE(addr, rw, us, pwt, pcd, a)              PAGE_ADDRESS(addr) | PDE_RW(rw) | \
                                                    PDE_US(us) | PAGE_LEVEL_WRITE_THROUGH(pwt) | \
                                                    PAGE_LEVEL_CACHE_DIS(pcd) | PDE_ACCESSED(a) | \
                                                    0x00000001
#define PDE_NOT_PRES                                0

#define PTE_DIRTY(x)                                (x << 6)
#define PTE_PAT(x)                                  (x << 7)
#define PTE_GLOBAL(x)                               (x << 8)
#define PTE_4K(addr, rw, us, pwt, pcd, a, pat, g)   PDE(addr, rw, us, pwt, pcd, a) | PTE_DIRTY(0) | \
                                                    PTE_PAT(pat) | PTE_GLOBAL(g)
#define PTE_NOT_PRES                                0
 
#endif