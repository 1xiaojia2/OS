.macro isr_stub vector, no_err=1
    .global isr_stub_\vector
    isr_stub_\vector:
        cli
        .if \no_err
            pushl $0x0    //push 0 as error_code if no err
        .endif
        pushl $\vector
        jmp isr_wrapper
.endm

.section .text

    .global _idt_flush
    _idt_flush:
        movl 4(%esp), %ecx
        lidt (%ecx)
        ret
    
    isr_wrapper:

        //TODO: Save all related registers

        //push param for isr_handler
        pushl %esp

        .extern isr_handler
        call isr_handler
        
        
        addl $0x0c, %esp

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


.section .data
.global isr_table
    .extern isr0
    .extern isr1
    .extern isr2
    .extern isr3
    .extern isr4
    .extern isr5
    .extern isr6
    .extern isr7
    .extern isr8
    .extern isr9
    .extern isr10
    .extern isr11
    .extern isr12
    .extern isr13
    .extern isr14
    .extern isr15
    .extern isr16
    .extern isr17
    .extern isr18
    .extern isr19
    .extern isr20
    .extern isr21
    .extern isr22
    .extern isr23
    .extern isr24
    .extern isr25
    .extern isr26
    .extern isr27
    .extern isr28
    .extern isr29
    .extern isr30
    .extern isr31


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
