#include <stdint.h>

#define EFLAGS_MBS	(1 << 1)
#define EFLAGS_IF_1	(1 << 9)
#define EFLAGS_IF_0	0
#define EFLAGS_IOPL_3	(3 << 12)
#define EFLAGS_IOPL_0	(0 << 12)

static inline void cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx){
    asm volatile(
        "cpuid\n\t"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(eax)
    );
}

static inline void rdmsr(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}
 
static inline void wrmsr(uint32_t msr, uint32_t lo, uint32_t hi)
{
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}

static inline uint32_t cpu_reflags(){
    uint32_t val;
    asm volatile("pushf\n"
                 "popl %0\n"
                 : "=r"(val)::);
    return val;
}

typedef enum{
    disable,
    enable,
} intr_status;

static inline intr_status cpu_get_intr_flag(){
    return ((cpu_reflags() >> 9) & 1);
}

static inline intr_status cli(){
    intr_status old = cpu_get_intr_flag();
    asm("cli");
    return old;
}

static inline void sti(){
    asm("sti");
}

void cpu_set_intr_flag(intr_status);


static inline uint32_t get_cr3(){
    uint32_t pd_addr;
    asm("movl %%cr3, %0\n\t"
        :"=r" (pd_addr)
        :
        : "memory");
    pd_addr &= 0xFFFFF000;
    return pd_addr;
}

static inline void load_cr3(uint32_t new_pd_addr){
    asm("movl %%cr3, %%eax\n\t"
        "orl $0xFFF, %%eax\n\t"
        "orl %0, %%eax\n\t"
        "movl %%eax, %%cr3\n\t"
        :
        : "m"(new_pd_addr)
        : "eax");
}
