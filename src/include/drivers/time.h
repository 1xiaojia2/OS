#ifndef _DRIVES_H
#define _DRIVES_H
#include <hardware/rtc.h>
#include <stdint.h>

typedef uint32_t time_t;

struct tm {
	int second;
	int minute;
	int hour;
	int mday;
	int month;
	int year;
    int century;
    int wday;
};

time_t sys_time();

#endif