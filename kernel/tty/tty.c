#include <LeeOS/kernel/tty/tty.h>
#include <libc/string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;



void terminal_initialize(){
    terminal_column = 0;
    terminal_row = 0;
    terminal_buffer = VGA_MEMORY;
    terminal_color = vga_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);

    for (size_t offset = 0; offset < VGA_WIDTH * VGA_HEIGHT; ++offset)
        terminal_buffer[offset] = vga_entry(' ', terminal_color);
}

void terminal_clear(){
    terminal_column = 0;
    terminal_row = 0;
    for (size_t offset = 0; offset < VGA_WIDTH * VGA_HEIGHT; ++offset)
        terminal_buffer[offset] = vga_entry(' ', terminal_color);
}

void terminal_set_color(uint8_t color){
    terminal_color = color;
}

void terminal_putchar(char c){
    if(c == '\n'){
        terminal_column = 0;

        if(++terminal_row == VGA_HEIGHT) 
            terminal_scroll_up(1);
    }
    
    // TODO: other escape character

    else{
        size_t offset = terminal_row * VGA_WIDTH + terminal_column;
        terminal_putchar_at(c, offset);
    }
}

void terminal_write(const char* str){
    size_t length = strlen(str);
    
    for (size_t index = 0; index < length; index++)
        terminal_putchar(str[index]);
}

void terminal_scroll_up(size_t line) {
    size_t offset = line  * VGA_HEIGHT;
    /* edge = (height - line ) * width*/
    size_t edge = (VGA_HEIGHT - line ) * VGA_WIDTH;
    
    for (size_t index = 0; index < edge; ++index)
        terminal_buffer[index] = terminal_buffer[index + offset];

    for (size_t index = edge; index < VGA_HEIGHT * VGA_WIDTH; ++index)
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    
    terminal_row = terminal_row - line  > 0 ? terminal_row - line : 0;
}


void terminal_putchar_at(char c, size_t offset) {
    
    terminal_buffer[offset] = vga_entry(c, terminal_color);
    
    if(++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        
        if(++terminal_row == VGA_HEIGHT) 
            terminal_scroll_up(1);
    }
}
