.macro  isr_stub vector, no_err=1
    .global isr_stub_\vector
    isr_stub_\vector:
        cli
        .if \no_err
            pushl $0x0
        .endif
        pushl $\vector
        jmp interrupt_wrapper
.endm

.macro  irq_stub vector
    .global irq_stub_\vector
    irq_stub_\vector:
        cli
        pushl $0x0
        pushl $(\vector+32)
        jmp interrupt_wrapper
.endm

.section .text
# General steps for interrupts and exceptions
interrupt_wrapper:

    pushl %esp

    call interrupt_handler

    addl $0x0C, %esp
    sti
    iret

    isr_stub 0
    isr_stub 1
    isr_stub 2
    isr_stub 3
    isr_stub 4
    isr_stub 5
    isr_stub 6
    isr_stub 7
    isr_stub 8, 0
    isr_stub 9
    isr_stub 10, 0
    isr_stub 11, 0
    isr_stub 12, 0
    isr_stub 13, 0
    isr_stub 14, 0
    isr_stub 15
    isr_stub 16
    isr_stub 17, 0
    isr_stub 18
    isr_stub 19
    isr_stub 20
    isr_stub 21
    isr_stub 22
    isr_stub 23
    isr_stub 24
    isr_stub 25
    isr_stub 26
    isr_stub 27
    isr_stub 28
    isr_stub 29
    isr_stub 30, 0
    isr_stub 31

    irq_stub 0
    irq_stub 1
    irq_stub 2
    irq_stub 3
    irq_stub 4
    irq_stub 5
    irq_stub 6
    irq_stub 7
    irq_stub 8
    irq_stub 9
    irq_stub 10
    irq_stub 11
    irq_stub 12
    irq_stub 13
    irq_stub 14
    irq_stub 15

    


