#ifndef _HARDWARE_8042_H
#define _HARDWARE_8042_H

typedef enum{
    ps2_data_port = 0x60,
    ps2_status_reg = 0x61,
    ps2_cmd_reg = 0x64,
};

void i8042_init();


#endif