.macro _isr_stub vector, no_err=1
    .global _isr_stub_\vector
    _isr_stub_\vector:
        cli
        .if \no_err
            pushl $0x0    /* push 0 as error_code if no err */
        .endif
        pushl $\vector
        jmp _isr_wrapper
.endm



.section .text
# General steps for interrupts and exceptions
_isr_wrapper:

    pushl %esp
    
    call isr_handler
    addl $0x0c, %esp
    sti
    iret

    _isr_stub 0
    _isr_stub 1
    _isr_stub 2
    _isr_stub 3
    _isr_stub 4
    _isr_stub 5
    _isr_stub 6
    _isr_stub 7
    _isr_stub 8, 0
    _isr_stub 9
    _isr_stub 10, 0
    _isr_stub 11, 0
    _isr_stub 12, 0
    _isr_stub 13, 0
    _isr_stub 14, 0
    _isr_stub 15
    _isr_stub 16
    _isr_stub 17, 0
    _isr_stub 18
    _isr_stub 19
    _isr_stub 20
    _isr_stub 21
    _isr_stub 22
    _isr_stub 23
    _isr_stub 24
    _isr_stub 25
    _isr_stub 26
    _isr_stub 27
    _isr_stub 28
    _isr_stub 29
    _isr_stub 30, 0
    _isr_stub 31
