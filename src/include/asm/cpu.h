#include <stdint.h>


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
