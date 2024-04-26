#ifndef _TTY_H
#define _TTY_H

#define VGA_TEXT_MODE 1
#define TAB 4

#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>

uint8_t tty_get_color();
void tty_set_color(uint8_t color);
void tty_init();
void tty_putchar(char c);
void tty_write(const char *s);
void tty_read(char *dest, size_t offset, size_t length);
void tty_cls();
void tty_write_with_color(const char *s, uint8_t color);


#endif
