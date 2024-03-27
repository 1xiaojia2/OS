#ifndef _PIC_H
#define _PIC_H 1
#include<stdint.h>
void pic_remap();

void pic_sendEOI(uint8_t irq);

#endif