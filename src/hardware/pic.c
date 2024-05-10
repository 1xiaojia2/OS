#include<asm/io.h>
#include<hardware/pic.h>

void pic_remap(){

	outb(PIC_MASTER_COMMAND, PIC_INIT);
    outb(PIC_SLAVE_COMMAND, PIC_INIT);

    outb(PIC_MASTER_DATA, 0x20);
    outb(PIC_SLAVE_DATA, 0x28);

    outb(PIC_MASTER_DATA, PIC_ICW1_INTERVAL4);
    outb(PIC_SLAVE_DATA, PIC_ICW1_SINGLE);

    outb(PIC_MASTER_DATA, PIC_ICW1_ICW4);
    outb(PIC_SLAVE_DATA, PIC_ICW1_ICW4);

    outb(PIC_MASTER_DATA, 0);
    outb(PIC_SLAVE_DATA, 0);
}

void pic_sendEOI(uint8_t irq){
	if(irq >= 8)
		outb(PIC_SLAVE_COMMAND,0x20);
 
	outb(PIC_MASTER_COMMAND,0x20);
}