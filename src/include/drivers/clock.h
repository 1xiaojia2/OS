#ifndef _TIME_H
#define _TIME_H 1
#include <x86/headers.h>

uint64_t time;

void init_timer();
void clock_handler(struct isr_regs *regs);

#endif