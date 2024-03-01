#ifndef _I386_IDT_H
#define _I386_IDT_H 1

#include <stdint.h>


#define GATE_PREVS(x)    (x << 15)
#define GATE_DPL(x)      ((x & 3) << 13)
#define GATE_SIZE(x)     (x << 11)


#define IDT_TASK_GATE_FLAG(PREVS, DPL)        GATE_PREVS(PREVS) | GATE_DPL(DPL) | \
                                                    GATE_SIZE(1)   | 0x0500
#define IDT_INT_GATE_FLAG(PREVS, DPL)         GATE_PREVS(PREVS) | GATE_DPL(DPL) | \
                                                    GATE_SIZE(1)   | 0x0600
#define IDT_TRAP_GATE_FLAG(PREVS, DPL)        GATE_PREVS(PREVS) | GATE_DPL(DPL) | \
                                                    GATE_SIZE(1)   | 0x0700    


void _idt_init();

#endif