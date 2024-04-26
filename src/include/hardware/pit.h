#ifndef _PIT_H
#define _PIT_H 1

#define PIT_CHANNEL0_PORT    0x40
#define PIT_CHANNEL1_PORT    0x41
#define PIT_CHANNEL2_PORT    0x42    /*PC Speaker.*/
#define PIT_MODE_REGS_PORT   0x43

#define SELECT_CHANNEL(channel) (((channel) & 0x02) << 6)
#define ACCESS_MODE(mode)       (((mode) & 0x02) << 4)
#define OPERATING_MODE(mode)    (((mode) & 0x03) << 1)
#define BCD_BINARY_MODE(mode)   ((mode) & 0x01)

#define PIT_MODE(sel, acc, oper, bcd_binary)    SELECT_CHANNEL(sel) | ACCESS_MODE(access) | \
                                                OPERATING_MODE(oper) | BCD_BINARY_MODE(bcd_binary)
        


enum pit_select_channel{
    channel_0 = 0,
    channel_1 = 1,
    channel_2 = 2,
    read_back = 3,
};


#endif