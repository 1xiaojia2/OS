#ifndef _TTY_TTY_H
#define _TTY_TTY_H

#include <stddef.h>
#include "vag.h"

void terminal_initialize();

void terminal_clear();

void terminal_set_color(uint8_t color);

void terminal_putchar(char c);

void terminal_putstr(const char* data);


#endif
