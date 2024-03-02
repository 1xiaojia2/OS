#ifndef _I386_GDT_H
#define _I386_GDT_H 1

#include <stdint.h>

struct gdt_entry
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;

}__attribute__((packed));

struct gdt_ptr_struct
{  
    uint16_t limit;
    struct gdt_entry *base;
}__attribute__((packed));

#define GDT_SIZE    5

#define GDT_ACCESS_CODE_DPL0    0x9A
#define GDT_ACCESS_DATA_DPL0    0x92
#define GDT_ACCESS_CODE_DPL3    0xFA
#define GDT_ACCESS_DATA_DPL3    0xF2

#define GDT_FLAGS               0xC0

extern void _gdtFlush(struct gdt_ptr_struct *addr);

void _setGdtEntry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void _initGdt();

#endif  /* _I386_GDT_H */