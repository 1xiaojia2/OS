#ifndef _I386_GDT_H
#define _I386_GDT_H 1

#include <stdint.h>

#define SEG_DESCTYPE(x) (x << 4)
#define SEG_DPL(x)      (x << 5)
#define SEG_PRES(x)     (x << 7)
#define SEG_AVL(x)      (x << 12)
#define SEG_LMODE(x)    (x << 13)
#define SEG_SIZE(x)     (x << 14)
#define SEG_GRAN(x)     (x << 15)

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define GDT_FLAG_CODE_DPL0      SEG_GRAN(1) | SEG_SIZE(1) | SEG_LMODE(0) | SEG_AVL(0) | \
                                SEG_PRES(1) | SEG_DPL(0)  | SEG_DESCTYPE(1) | SEG_CODE_EXRD

#define GDT_FLAG_DATA_DPL0      SEG_GRAN(1) | SEG_SIZE(1) | SEG_LMODE(0) | SEG_AVL(0) | \
                                SEG_PRES(1) | SEG_DPL(0)  | SEG_DESCTYPE(1) | SEG_DATA_RDWR

#define GDT_FLAG_CODE_DPL3      SEG_GRAN(1) | SEG_SIZE(1) | SEG_LMODE(0) | SEG_AVL(0) | \
                                SEG_PRES(1) | SEG_DPL(3)  | SEG_DESCTYPE(1) | SEG_CODE_EXRD

#define GDT_FLAG_DATA_DPL3      SEG_GRAN(1) | SEG_SIZE(1) | SEG_LMODE(0) | SEG_AVL(0) | \
                                SEG_PRES(1) | SEG_DPL(3)  | SEG_DESCTYPE(1) | SEG_DATA_RDWR

void _create_gdt_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
void _gdt_init();

#endif  /* _I386_GDT_H */