#ifndef _GDT_H
#define _GDT_H 1
#include<stdint.h>
#include<stddef.h>

#define GDT_ACCESS_CODE_DPL0    0x9A
#define GDT_ACCESS_DATA_DPL0    0x92
#define GDT_ACCESS_CODE_DPL3    0xFA
#define GDT_ACCESS_DATA_DPL3    0xF2
#define GDT_FLAGS               0xC0
#define GDT_SIZE    5

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

void init_gdt();
void set_gdt_entry(size_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
extern void gdt_flush(struct gdt_ptr_struct gdt_ptr);

#endif