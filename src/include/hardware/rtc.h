#ifndef _RTC_H
#define _RTC_H

typedef enum rtc_port{
    rtc_address = 0x70,
    rtc_data = 0x71,
} rtc_port;

#define SECONDS                 0x00
#define ALARM_SECONDS           0X01
#define MINUTES                 0x02
#define ALARM_MINUTES           0X03
#define HOURS                   0x04
#define ALARM_HOURS             0X05
#define DAY_OF_WEEK             0x06
#define DAY_OF_MONTH            0x07
#define MONTH                   0x08
#define YEAR                    0x09
#define RETISTER_A              0x0A
#define REGISTER_B              0x0B
#define REGISTER_C              0x0C
#define REGISTER_D              0x0D



#endif