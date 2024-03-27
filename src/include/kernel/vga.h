#ifdef VGA_TEXT_MODE
#include <stdint.h>
#include <stddef.h>
#include <asm/io.h>

#define VGA_MEMORY_START 	0xC00B8000
#define VGA_WIDTH 			80
#define VGA_HEIGHT			25
#define VGA_ENTRY_LIMIT		2000

enum vga_color {
    VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


static inline uint8_t vga_set_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t attributes) {
	return (uint16_t) c | (uint16_t) attributes << 8;
}

static inline void vga_update_cursor(uint32_t curosr){
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (curosr & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((curosr >> 8) & 0xFF));
}

#endif