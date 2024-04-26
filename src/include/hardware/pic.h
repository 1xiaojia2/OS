#ifndef _PIC_H
#define _PIC_H 1
#include<stdint.h>

#define PIC_MASTER_COMMAND     0x20
#define PIC_SLAVE_COMMAND      0xA0
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_DATA      0xA1

#define PIC_INIT            0x11
#define PIC_ICW1_ICW4	    0x01		/* Indicates that ICW4 will be present */
#define PIC_ICW1_SINGLE	    0x02		/* Single (cascade) mode */
#define PIC_ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */

#define PIC_ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */


void pic_remap();
void pic_sendEOI(uint8_t irq);

#endif