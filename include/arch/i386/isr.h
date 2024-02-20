#ifndef _ISR_H
#define _ISR_H

#include <stdint.h>

#define DIVIDE_ERROR                    0
#define DEBUG_EXCEPTION                 1
#define NMI                             2
#define BREAKPOINT                      3
#define OVERFLOW                        4
#define BOUND_RANGE_EXCEEDED            5
#define INVALID_OPCODE                  6
#define DEVICE_NOT_AVAILABLE            7
#define DEUBLE_FAULT                    8
#define COPROCESSOR_SEGMENT_OVERRUN     9
#define INVALID_TSS                     10
#define SEGMENT_NOT_PRESENT             11
#define STACK_SEGMENT_FAULT             12
#define GENERAL_PROTECTION              13
#define PAGE_FAULT                      14
#define RESERVED_15                     15
#define MATH_FAULT                      16
#define ALIGNMENT_CHECK                 17
#define MACHINE_CHECK                   18
#define SIMD_FP_EXCEPTION               19
#define VIRTUALIZATION_EXCEPTION        20
#define CONTROL_PROTECTION_EXCEPTION    21

struct interrupt_frame
{
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
};

void isr0(struct interrupt_frame* frame);

#endif