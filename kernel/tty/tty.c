#include <stddef.h>
#include <LeeOS/kernel/tty/tty.h>
#include <libc/string/string.h>

#define TTY_WIDTH           80
#define TTY_HEIGHT          25

#define TTY_BUFFER_START    0xB8000
#define TTY_BUGGER_LENGTH   TTY_WIDTH * TTY_HEIGHT


static size_t tty_column;
static size_t tty_row;
static uint8_t tty_color;
static uint16_t* tty_buffer;


void tty_initialize(){
    tty_column = 0;
    tty_row = 0;
    
    tty_buffer = (uint16_t*)TTY_BUFFER_START;

    tty_color = vga_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);

    for (size_t offset = 0; offset < TTY_BUGGER_LENGTH; ++offset)
        tty_buffer[offset] = vga_entry(' ', tty_color);
}

void tty_put_char(char c){
    if(c == '\n'){
        tty_column = 0;

        if(++tty_row == TTY_HEIGHT) 
            tty_scroll_up(1);
    } 
    
    // TODO: other escape character

    else{
        size_t offset = tty_row * TTY_WIDTH + tty_column;
        tty_put_char_at(c, offset);
    }
}

void tty_put_str(const char* str){
    size_t length = strlen(str);
    
    for (size_t index = 0; index < length; index++)
        tty_put_char(str[index]);
}

void tty_put_char_at(char c, size_t offset) {
    
    tty_buffer[offset] = vga_entry(c, tty_color);
    
    if(++tty_column == TTY_WIDTH) {
        tty_column = 0;
        
        if(++tty_row == TTY_HEIGHT) 
            tty_scroll_up(1);
    }
}

void tty_scroll_up(size_t count) {
    size_t offset = count * TTY_WIDTH;
    /* edge = (height - count) * width*/
    size_t edge = (TTY_HEIGHT - count) * TTY_WIDTH;
    
    for (size_t index = 0; index < edge; ++index)
        tty_buffer[index] = tty_buffer[index + offset];

    for (size_t index = edge; index < TTY_BUGGER_LENGTH; ++index)
        tty_buffer[index] = vga_entry(' ', tty_color);
    
    tty_row = tty_row - count > 0 ? tty_row - count : 0;
}
