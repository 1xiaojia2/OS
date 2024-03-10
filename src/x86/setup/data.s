.global isr_table, idt, idt_ptr, gdt, gdt_ptr

.section .data

isr_table:
    .long isr0
    .long isr1
    .long isr2
    .long isr3
    .long isr4
    .long isr5
    .long isr6
    .long isr7
    .long isr8
    .long isr9
    .long isr10
    .long isr11
    .long isr12
    .long isr13
    .long isr14
    .long isr15
    .long isr16
    .long isr17
    .long isr18
    .long isr19
    .long isr20
    .long isr21
    .long isr22
    .long isr23
    .long isr24
    .long isr25
    .long isr26
    .long isr27
    .long isr28
    .long isr29
    .long isr30
    .long isr31

.section .bss

.align 4096
idt:
    .skip 8 * 256
gdt:
    .skip 8 * 5 
mbi:
    .skip
idt_ptr:
    .skip 6
gdt_ptr:
    .skip 6
