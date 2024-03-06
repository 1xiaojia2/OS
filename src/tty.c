#include <kernel/tty.h>
#include <string.h>

static size_t offset;
static uint8_t current_color;
static const uint8_t default_color = VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
static uint16_t* const buffer = (uint16_t*)VGA_MEMORY_START;


void tty_set_color(uint8_t color){
    current_color = color;
}

void tty_scroll_up(){
    for (size_t i = VGA_WIDTH; i < VGA_ENTRY_LIMIT; i++)
        buffer[i - VGA_WIDTH] = buffer[i];
    for (size_t i = VGA_ENTRY_LIMIT - VGA_WIDTH; i < VGA_ENTRY_LIMIT; i++)
        buffer[i] = vga_entry(' ', current_color);
    offset = VGA_ENTRY_LIMIT - VGA_WIDTH;
}

void check(){
    if(offset < VGA_ENTRY_LIMIT)
        return;
    tty_scroll_up();
}

void new_line(){
    size_t remainder = VGA_WIDTH - (offset % VGA_WIDTH);
    for (size_t i = 0; i < remainder; i++)
    {
        buffer[offset++] = vga_entry(' ', current_color);
        check();
    }
}

void tty_putchar_at(char c, size_t i){
    buffer[i] = vga_entry(c, current_color);
    check();
}

void tty_putchar(char c) {
    switch (c)
    {
    case '\n':
        new_line();
        break;
    default:
        tty_putchar_at(c, offset++);
        break;
    }   
}

void tty_init(){
    offset = 0;
    current_color = default_color;
    for (size_t i = 0; i < VGA_ENTRY_LIMIT; i++)
        buffer[i] = vga_entry(' ', current_color);

}
void tty_write(const char *s){
    size_t length = strlen(s);
    for (size_t i = 0; i < length; i++)
        tty_putchar(s[i]);
}

void tty_read(char *dest, size_t offset, size_t length) {
    for (size_t i = 0; i < length; i++)
        dest[i] = buffer[offset + i] & 0xFF;
}


void tty_cls(){
    uint8_t color = current_color;
    tty_init();
    tty_set_color(color);
}


