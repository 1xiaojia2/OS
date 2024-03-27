#include<stdint.h>
#include<asm/io.h>

uint64_t ticks;
const uint32_t freq = 100;

void onIrq0(struct isr_regs *regs){
    ticks += 1;
}

void init_timer(){
    ticks = 0;
    irq_install_handler(0,onIrq0);

    //119318.16666 Mhz
    uint32_t divisor = 1193180/freq;

    //0011 0110
    outb(0x43,0x36);
    outb(0x40,(uint8_t)(divisor & 0xFF));
    outb(0x40,(uint8_t)((divisor >> 8) & 0xFF));
}