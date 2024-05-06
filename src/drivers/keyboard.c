#include <asm/io.h>
#include <stdint.h>
#include <stdio.h>

void keyboard_handler(struct isr_regs *regs){
    uint32_t scan_code = inb(0x60);
    printf("Scan code: %u\n", scan_code);
}

void init_keryboard(){
    irq_install_handler(1, keyboard_handler);
}

