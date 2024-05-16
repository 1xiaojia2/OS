#include <drivers/console.h>
#include <kernel/sync.h>
#include <kernel/tty.h>

static struct lock console_lock;

static uint8_t console_color;

void console_init(){
    lock_init(&console_lock);
}
void console_acquire(){
    lock_acquire(&console_lock);
}
void console_release(){
    lock_release(&console_lock);
}

void console_write(char * str){
    console_acquire();
    tty_write(str);
    console_release();
}

void console_putchar(char c){
    console_acquire();
    tty_putchar(c);
    console_release();
}

void console_change_color(uint8_t color){
    console_acquire();
    tty_set_color(color);
    console_release();
}

void console_write_with_color(char *str, uint8_t color){
    console_acquire();
    tty_write_with_color(str, color);
    console_release();

}