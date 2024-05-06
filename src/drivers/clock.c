#include<stdint.h>
#include<hardware/pit.h>
#include<kernel/header.h>
#include<drivers/clock.h>

uint64_t ticks;

void clock_handler(struct isr_regs *regs){
    ticks++;
}

void init_timer(){
    ticks = 0;
    irq_install_handler(0,clock_handler);
    
    uint32_t divisor = PIT_OSCILLATOR/CLOCK_PER_SEC;
    
    write_pit_count(CONTROL_WORD_REG(SC_0, 3, 2, 0), counter0, divisor);
}

