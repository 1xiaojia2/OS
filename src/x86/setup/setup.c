#include "setup.h"
#include <string.h>

extern uint32_t *mbi;

void setup(unsigned address){
    init_gdt();
    init_idt();
    memcpy(mbi, (void *)address, *(unsigned *)address);
}
