#include <kernel/sys/syscall.h>
#include <drivers/time.h>
#include <stdio.h>
#include <kernel/tty.h>
#include <drivers/clock.h>

void bare_show_time(){
    struct tm time;
    read_rtc(&time);
    printf("%d%d/%d/%d %d:%d:%d\n", time.century, time.year, time.month, time.mday, time.hour, 
        time.minute, time.second);
}

void bare_cls(){
    tty_cls();
}

static uint8_t color_table[16] = {
	0 | 0 << 4,
	1 | 0 << 4,
	2 | 0 << 4,
	3 | 0 << 4,
	3 | 0 << 4,
	7 | 0 << 4,
	9 | 0 << 4,
	10 | 0 << 4,
	11 | 0 << 4,
	12 | 0 << 4,
	13 | 0 << 4,
	15 | 0 << 4,
};
int current = 0;

void roll_line1(uintptr_t *line){
    tty_roll_line(*line, true);
    tty_change_line_color(*line, color_table[(current++)%12]);
}

void roll_line2(uintptr_t *line){
    tty_roll_line(*line, false);
    tty_change_line_color(*line, color_table[(current++)%12]);
}

void bare_roll_line(){
    uintptr_t *ptr0 = kmalloc(sizeof(int));
    uintptr_t *ptr1 = kmalloc(sizeof(int));
    *ptr0 = 0;
    add_alarm_task(roll_line1, ptr0, 500, re_triggerable);
    *ptr1 = 1;
    add_alarm_task(roll_line2, ptr1, 500, re_triggerable);
}

void bare_cancel_roll(){
    delete_alarm_task(roll_line1);
    delete_alarm_task(roll_line2);
}