#ifndef _PIT_H
#define _PIT_H 1
#include <stdint.h>

typedef enum pit_port{
    counter0 = 0x40,
    counter1 = 0x41,
    counter2 = 0x42,
    control_word_reg = 0x43,
} pit_port;

#define PIT_OSCILLATOR      1193182

#define SC_0            0
#define SC_1            1
#define SC_2            2
#define SC_READ_BACK    3

#define SELECT_COUNTER(counter) (((counter) & 0x03) << 6)
#define RW(acc)       (((acc) & 0x03) << 4)
#define OPERATING_MODE(mode)    (((mode) & 0x07) << 1)
#define BCD(enable)   ((enable) & 0x01)

#define CONTROL_WORD_REG(sel, acc, mode, enable)    SELECT_COUNTER(sel) | RW(acc) | \
                                                OPERATING_MODE(mode) | BCD(enable)

uint32_t read_pit_count(pit_port counter);
void write_pit_count(pit_port cw, pit_port counter, uint32_t divisor);

#endif