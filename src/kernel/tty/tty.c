#include <kernel/tty.h>
#include <string.h>

static uint32_t cursor;
static uint8_t current_color;
static const uint8_t default_color = VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
static uint16_t* vga = (uint16_t *)VGA_MEMORY_START;

void tty_set_color(uint8_t color){
    current_color = color;
}

uint8_t tty_get_color(){
    return current_color;
}

void tty_scroll_up(){
    for (size_t i = VGA_WIDTH; i < VGA_ENTRY_LIMIT; i++)
        vga[i - VGA_WIDTH] = vga[i];
    for (size_t i = VGA_ENTRY_LIMIT - VGA_WIDTH; i < VGA_ENTRY_LIMIT; i++)
        vga[i] = vga_entry(' ', current_color);
    cursor = VGA_ENTRY_LIMIT - VGA_WIDTH;
}

void check(){
    /* Is the vga full? */
    if(cursor < VGA_ENTRY_LIMIT)
        return;
    tty_scroll_up();
}

void new_line(){
    size_t remainder = VGA_WIDTH - (cursor % VGA_WIDTH);
    for (size_t i = 0; i < remainder; i++)
    {
        vga[cursor++] = vga_entry(' ', current_color);
        check();
    }
}

void tty_putchar_at(char c, size_t i){
    vga[i] = vga_entry(c, current_color);
    check();
}

void tty_putchar(char c) {
    switch (c)
    {
    case '\n':
        new_line();
        break;
    case '\t':
        for (size_t i = 0; i < TAB - (cursor % TAB); i++)
            tty_putchar_at(' ', cursor++);
        break;
    case '\b':
        if(cursor)
            tty_putchar_at(' ', --cursor);
        break;
    default:
        tty_putchar_at(c, cursor++);
        break;
    }
    vga_update_cursor(cursor);
}

void tty_init(){
    cursor = 0;
    current_color = default_color;
    for (size_t i = 0; i < VGA_ENTRY_LIMIT; i++)
        vga[i] = vga_entry(' ', current_color);
}
void tty_write(const char *s){
    size_t length = strlen(s);
    for (size_t i = 0; i < length; i++)
        tty_putchar(s[i]);
}

void tty_write_with_color(const char *s, uint8_t color){
    uint8_t pre_color = current_color;
    tty_set_color(color);
    tty_write(s);
    tty_set_color(pre_color);
}

void tty_read(char *dest, size_t cursor, size_t length) {
    for (size_t i = 0; i < length; i++)
        dest[i] = vga[cursor + i] & 0xFF;
}


void tty_cls(){
    uint8_t color = current_color;
    tty_init();
    tty_set_color(color);
}


