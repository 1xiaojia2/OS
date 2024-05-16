#ifndef __CONSOLE_H
#define __CONSOLE_H
#include <stdint.h>

void console_init();
void console_write(char *);
void console_putchar(char);
void console_write_with_color(char *str, uint8_t color);
void console_change_color(uint8_t color);
#endif