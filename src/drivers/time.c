#include <drivers/time.h>
#include <hardware/rtc.h>
#include <kernel/header.h>

#define MINUTE 60
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)
#define YEAR (365*DAY)

time_t kernel_mktime(struct tm * tm);

/* interestingly, we assume leap-years */
static int month[12] = {
	0,
	DAY*(31),
	DAY*(31+29),
	DAY*(31+29+31),
	DAY*(31+29+31+30),
	DAY*(31+29+31+30+31),
	DAY*(31+29+31+30+31+30),
	DAY*(31+29+31+30+31+30+31),
	DAY*(31+29+31+30+31+30+31+31),
	DAY*(31+29+31+30+31+30+31+31+30),
	DAY*(31+29+31+30+31+30+31+31+30+31),
	DAY*(31+29+31+30+31+30+31+31+30+31+30)
};

time_t sys_time(){
	struct tm time;
	read_rtc(&time);
	time_t time_stamp = kernel_mktime(&time);
	time_stamp += TIMEZONE * HOUR;
	return time_stamp;
}

time_t kernel_mktime(struct tm * tm)
{
	time_t res;
	int year;
	year = 30 + tm->year;
/* magic offsets (y+1) needed to get leapyears right.*/
	res = YEAR*year + DAY*((year+1)/4);
	res += month[tm->month];
/* and (y+2) here. If it wasn't a leap-year, we have to adjust */
	if (tm->month>1 && ((year+2)%4))
		res -= DAY;
	res += DAY*(tm->mday-1);
	res += HOUR*tm->hour;
	res += MINUTE*tm->minute;
	res += tm->second;
	return res;
}