.macro  intr_stub vector, no_err=1
    .global intr_stub_\vector
    intr_stub_\vector:
        cli
        .if \no_err
            pushl $0x0
        .endif
        pushl $\vector
        jmp intr_wrapper
.endm


.extern intr_handler

.section .text
# General steps for interrupts and exceptions
intr_wrapper:
    # eax, ecx, edx, ebx
    # esp, ebp
    # esi, edi
    pushal

    # ds, es, fs, gs
    xorl %eax, %eax
    movw %ds, %ax
    pushl %eax
    movw %es, %ax
    pushl %eax
    movw %fs, %ax
    pushl %eax
    movw %gs, %ax
    pushl %eax

    movl %cr2, %eax
    pushl %eax

    movl $0x10, %eax  # DPL = 0, data
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp

    call intr_handler

.global soft_iret
soft_iret:
    pop %esp

    pop %eax
    
    pop %eax
    movw %ax, %gs
    pop %eax
    movw %ax, %fs
    pop %eax
    movw %ax, %es
    pop %eax
    movw %ax, %ds

    popal

    addl $0x08, %esp
    
    sti
    iret

    intr_stub 0
    intr_stub 1
    intr_stub 2
    intr_stub 3
    intr_stub 4
    intr_stub 5
    intr_stub 6
    intr_stub 7
    intr_stub 8, no_err=0
    intr_stub 9
    intr_stub 10, no_err=0
    intr_stub 11, no_err=0
    intr_stub 12, no_err=0
    intr_stub 13, no_err=0
    intr_stub 14, no_err=0
    intr_stub 15
    intr_stub 16
    intr_stub 17, no_err=0
    intr_stub 18
    intr_stub 19
    intr_stub 20
    intr_stub 21
    intr_stub 22
    intr_stub 23
    intr_stub 24
    intr_stub 25
    intr_stub 26
    intr_stub 27
    intr_stub 28
    intr_stub 29
    intr_stub 30, no_err=0
    intr_stub 31, no_err=0

    intr_stub 32
    intr_stub 33
    intr_stub 34
    intr_stub 35
    intr_stub 36
    intr_stub 37
    intr_stub 38
    intr_stub 39
    intr_stub 40
    intr_stub 41
    intr_stub 42
    intr_stub 43
    intr_stub 44
    intr_stub 45
    intr_stub 46
    intr_stub 47

    intr_stub 128

.section .data
.global intr_table
intr_table:
    .long intr_stub_0
    .long intr_stub_1
    .long intr_stub_2
    .long intr_stub_3
    .long intr_stub_4
    .long intr_stub_5
    .long intr_stub_6
    .long intr_stub_7
    .long intr_stub_8
    .long intr_stub_9
    .long intr_stub_10
    .long intr_stub_11
    .long intr_stub_12
    .long intr_stub_13
    .long intr_stub_14
    .long intr_stub_15
    .long intr_stub_16
    .long intr_stub_17
    .long intr_stub_18
    .long intr_stub_19
    .long intr_stub_20
    .long intr_stub_21
    .long intr_stub_22
    .long intr_stub_23
    .long intr_stub_24
    .long intr_stub_25
    .long intr_stub_26
    .long intr_stub_27
    .long intr_stub_28
    .long intr_stub_29
    .long intr_stub_30
    .long intr_stub_31
    .long intr_stub_32
    .long intr_stub_33
    .long intr_stub_34
    .long intr_stub_35
    .long intr_stub_36
    .long intr_stub_37
    .long intr_stub_38
    .long intr_stub_39
    .long intr_stub_40
    .long intr_stub_41
    .long intr_stub_42
    .long intr_stub_43
    .long intr_stub_44
    .long intr_stub_45
    .long intr_stub_46
    .long intr_stub_47