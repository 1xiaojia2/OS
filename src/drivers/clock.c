#include<stdint.h>
#include<asm/io.h>
#include<hardware/pit.h>
#include<drivers/timer.h>

uint64_t ticks;
const uint32_t freq = 21;

void onIrq0(struct isr_regs *regs){
    ticks += 1;
}

void init_timer(){
    ticks = 0;
    irq_install_handler(0,onIrq0);
    //119318.16666 Mhz
    uint32_t divisor = 1193180/freq;
    
    //0011 0110
    outb(PIT_MODE_REGS_PORT,0x36);
    outb(PIT_CHANNEL0_PORT,(uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0_PORT,(uint8_t)((divisor >> 8) & 0xFF));
}

unsigned read_pit_count() {
	unsigned count = 0;
 
	// Disable interrupts
	cli();
 
	// al = channel in bits 6 and 7, remaining bits clear
	outb(PIT_MODE_REGS_PORT,0b0000000);
 
	count = inb(0x40);		// Low byte
	count |= inb(0x40)<<8;		// High byte

    sti();

	return count;
}

