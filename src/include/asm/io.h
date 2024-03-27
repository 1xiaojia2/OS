#ifndef _IO_H
#define _IO_H 1

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val){
    asm volatile("outb %0, %1" : : "a"(val), "dN"(port));
}

static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void io_wait(void){
    outb(0x80, 0);
}

#endif