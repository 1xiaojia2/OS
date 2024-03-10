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

struct idt_entry
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t access;
    uint16_t offset_high;

}__attribute__((packed));

struct idt_ptr_struct
{
    uint16_t limit;
    struct idt_entry *base;
}__attribute__((packed));

struct isr_regs
{
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
};


#define GDT_SIZE    5
#define GDT_ACCESS_CODE_DPL0    0x9A
#define GDT_ACCESS_DATA_DPL0    0x92
#define GDT_ACCESS_CODE_DPL3    0xFA
#define GDT_ACCESS_DATA_DPL3    0xF2
#define GDT_FLAGS               0xC0

#define IDT_SIZE       256
#define IDT_INTR_ACCESS_DPL0 0x8E

void setup(unsigned address);

void init_gdt();
void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

void init_idt();
void set_idt_entry(uint8_t vector, void* isr, uint16_t segment_selector, uint8_t access);

extern void _isr_stub_0();
extern void _isr_stub_1();
extern void _isr_stub_2();
extern void _isr_stub_3();
extern void _isr_stub_4();
extern void _isr_stub_5();
extern void _isr_stub_6();
extern void _isr_stub_7();
extern void _isr_stub_8();
extern void _isr_stub_9();
extern void _isr_stub_10();
extern void _isr_stub_11();
extern void _isr_stub_12();
extern void _isr_stub_13();
extern void _isr_stub_14();
extern void _isr_stub_15();
extern void _isr_stub_16();
extern void _isr_stub_17();
extern void _isr_stub_18();
extern void _isr_stub_19();
extern void _isr_stub_20();
extern void _isr_stub_21();
extern void _isr_stub_22();
extern void _isr_stub_23();
extern void _isr_stub_24();
extern void _isr_stub_25();
extern void _isr_stub_26();
extern void _isr_stub_27();
extern void _isr_stub_28();
extern void _isr_stub_29();
extern void _isr_stub_30();
extern void _isr_stub_31();
