#include <hardware/i8042.h>
#include <asm/cpu.h>

void i8042_init(){
    cli();

    sti();
}