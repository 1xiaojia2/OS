#include <kernel/mm/pmm.h>
#include <kernel/syslog.h>
#include <kernel/header.h>
#include <stddef.h>
#include <stdbool.h>

#define DIV_ROUND_UP(address)   (((address)+PAGE_SIZE-1)/PAGE_SIZE)

static uint32_t bitmap[1024 * 1024 / BITMAP_GRAN];
extern unsigned _kernel_end;
static uint32_t pre_alloc_pp;
static uint32_t total_page;
static uint32_t free_page;

int bitmap_used(uint32_t pp);
int bitmap_free(uint32_t pp);
bool bitmap_get(uint32_t pp);
int bitmap_set(uint32_t pp, size_t count, bool flag);

static unsigned *bitmap_func[] = {bitmap_used, bitmap_free};



static inline void oom(){
    printk(MEMORY, ERROR, "Out of memory.");
    while (1){}
}

void pmm_init(uint32_t mem_lower, uint32_t mem_upper){
    unsigned kernel_end = (unsigned)(&_kernel_end) - KERNEL_BASE;
    total_page = DIV_ROUND_UP(mem_upper);
    free_page = 0;
    bitmap_set(DIV_ROUND_UP(kernel_end), (mem_upper - kernel_end) >> 12, FREE);
}

/**
 *  Find a free physical page and return the base address of this page.
 *  If 'oom', return NULL. 
*/
void *pm_alloc(){
    if(free_page == 0){
        printk(MEMORY, ERROR, "No avalible memory.");
        return NULL;
    }

    size_t alloc_free_pp;
    for (alloc_free_pp = pre_alloc_pp; alloc_free_pp < total_page; alloc_free_pp++)
        if(bitmap_get(alloc_free_pp) == FREE) {
            bitmap_set(alloc_free_pp, 1, USED);
            pre_alloc_pp = alloc_free_pp;
            return (void *)(alloc_free_pp << 12);
        }

    for (alloc_free_pp = 0; alloc_free_pp < pre_alloc_pp; alloc_free_pp++)
        if(bitmap_get(alloc_free_pp) == FREE) {
            bitmap_set(alloc_free_pp, 1, USED);
            pre_alloc_pp = alloc_free_pp;
            return (void *)(alloc_free_pp << 12);
        }
}

/**
 * Free physical page 'pp'.
*/
int pm_free(uint32_t pp){
    if(pp >= total_page){
        oom();
    }
    return bitmap_set(pp, 1, FREE);
}

int bitmap_set(uint32_t pp, size_t count, bool flag){
    
    /**
     * TODO:
     *  Optimizing algorithom
    */
    int status;
    int (*bitmap_set_op)(uint32_t) = bitmap_func[flag];
    for (size_t i = 0; i < count; i++){
        status = bitmap_set_op(pp + i);
        if(status != 0)
            return status;
    }
    return status;
}

bool bitmap_get(uint32_t pp){
    return (bitmap[BITMAP_BYTE_INDEX(pp)] >> ((BITMAP_BIT_OFFSET(pp)))) & 1;
}

int bitmap_used(uint32_t pp){
    if(free_page == 0) return -1;
    if(bitmap_get(pp) == USED) return 1;
    bitmap[BITMAP_BYTE_INDEX(pp)] &= ~(1 << BITMAP_BIT_OFFSET(pp));
    free_page--;
    return 0;
}

int bitmap_free(uint32_t pp){
    if(free_page == total_page) return -1;
    if(bitmap_get(pp) == FREE) return 1;
    bitmap[BITMAP_BYTE_INDEX(pp)] |= (1 << BITMAP_BIT_OFFSET(pp));
    free_page++;
    return 0;
}
