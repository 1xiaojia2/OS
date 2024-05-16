#ifndef _KERYBOARD_H
#define _KERYBOARD_H

#include <x86/headers.h>
#include <ds/ioqueue.h>

void keyboard_handler(struct isr_regs *regs);

void init_keryboard();
extern struct ioqueue kbd_buf;

#endif