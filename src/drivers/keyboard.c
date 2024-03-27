#include <asm/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <kernel/tty.h>


void keyboard_handler(struct isr_regs *regs){
    uint32_t scanCode = inb(0x60) & 0x7F; //What key is pressed
    uint32_t press = inb(0x60) & 0x80; //Press down, or released

}

void init_keryboard(){
    irq_install_handler(1, keyboard_handler);
}

