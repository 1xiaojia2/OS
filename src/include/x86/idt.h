#ifndef _IDT_H
#define _IDT_H
#include <stddef.h>
#include <stdint.h>

#define IDT_SIZE    256
#define IDT_INTR_ACCESS_DPL0 0x8E

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

void init_idt();
void set_idt_entry(uint8_t vector, uintptr_t isr, uint16_t segment_selector, uint8_t access);
extern void idt_flush(struct idt_ptr_struct *idt_ptr);

extern void intr_stub_0();
extern void intr_stub_1();
extern void intr_stub_2();
extern void intr_stub_3();
extern void intr_stub_4();
extern void intr_stub_5();
extern void intr_stub_6();
extern void intr_stub_7();
extern void intr_stub_8();
extern void intr_stub_9();
extern void intr_stub_10();
extern void intr_stub_11();
extern void intr_stub_12();
extern void intr_stub_13();
extern void intr_stub_14();
extern void intr_stub_15();
extern void intr_stub_16();
extern void intr_stub_17();
extern void intr_stub_18();
extern void intr_stub_19();
extern void intr_stub_20();
extern void intr_stub_21();
extern void intr_stub_22();
extern void intr_stub_23();
extern void intr_stub_24();
extern void intr_stub_25();
extern void intr_stub_26();
extern void intr_stub_27();
extern void intr_stub_28();
extern void intr_stub_29();
extern void intr_stub_30();
extern void intr_stub_31();
extern void intr_stub_32();
extern void intr_stub_33();
extern void intr_stub_34();
extern void intr_stub_35();
extern void intr_stub_36();
extern void intr_stub_37();
extern void intr_stub_38();
extern void intr_stub_39();
extern void intr_stub_40();
extern void intr_stub_41();
extern void intr_stub_42();
extern void intr_stub_43();
extern void intr_stub_44();
extern void intr_stub_45();
extern void intr_stub_46();
extern void intr_stub_47();

#endif