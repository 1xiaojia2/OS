#ifndef _TTY_TTY_H
#define _TTY_TTY_H

#include <stddef.h>
#include "vag.h"

void terminal_initialize(void);

void terminal_clear();

void terminal_set_color(uint8_t color);

void terminal_putchar(char c);

void terminal_write(const char* data);

void terminal_scroll_up(size_t line);

void terminal_putchar_at(char c, size_t offset);

#endif
