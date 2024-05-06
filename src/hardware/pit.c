#include <hardware/pit.h>
#include <asm/io.h>
#include <asm/cpu.h>

uint32_t read_pit_count(pit_port counter){
	uint32_t count = 0;
 
	cli();
 
	outb(control_word_reg, SELECT_COUNTER(SC_0));   // counter latch command
 
	count = inb(counter);       // LSB
	count |= inb(counter)<<8;   // MSB

    sti();

	return count;
}

void write_pit_count(pit_port cw, pit_port counter, uint32_t divisor){
    cli();
    outb(control_word_reg,cw);
    outb(counter,(uint8_t)(divisor & 0xFF));
    outb(counter,(uint8_t)((divisor >> 8) & 0xFF));
    sti();
}