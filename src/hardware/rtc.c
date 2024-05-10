#include <hardware/rtc.h>
#include <asm/io.h>
 
int get_update_in_progress_flag() {
      outb(rtc_address, 0x0A);
      return (inb(rtc_data) & 0x80);
}
 
unsigned char get_RTC_register(int reg) {
      outb(rtc_address, reg);
      return inb(rtc_data);
}

static inline int bcd2bin(int num){
    return (num & 0x0F) + ((num / 16) * 10);
}
 
void read_rtc(struct tm *time){
    do {
        time->second = get_RTC_register(SECONDS);
        time->minute = get_RTC_register(MINUTES);
        time->hour = get_RTC_register(HOURS);
        time->mday = get_RTC_register(DAY_OF_MONTH);
        time->wday = get_RTC_register(DAY_OF_WEEK);
        time->month = get_RTC_register(MONTH);
        time->year = get_RTC_register(YEAR);
        time->century = get_RTC_register(CENTURY);
    } while( (time->second != get_RTC_register(SECONDS)));

    time->second = bcd2bin(time->second);
    time->minute = bcd2bin(time->minute);
    time->hour = bcd2bin(time->hour);
    time->mday = bcd2bin(time->mday);
    time->month = bcd2bin(time->month);
    time->year = bcd2bin(time->year);
    time->century = bcd2bin(time->century);
}