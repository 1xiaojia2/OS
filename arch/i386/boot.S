#include <arch/i386/multiboot.h>

#define STACK_SIZE  0x4000

.section .multiboot
    .align  8
    multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_ARCHITECTURE_I386
        .long   multiboot_header_end - multiboot_header
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_ARCHITECTURE_I386 + multiboot_header_end - multiboot_header)

    nultiboot_header_tag_end:
        .short  MULTIBOOT_HEADER_TAG_END_TYPE
        .short  0
        .long   MULTIBOOT_HEADER_TAG_END_SIZE
    multiboot_header_end:

.section .bss
    .align  16
    stack_bottom:
        .skip   STACK_SIZE
    stack_top:

.section .text
    .global _start
    _start:
        movl $stack_top, %esp

        call _kernel_init

        call load_gdt

        call load_idt

        call enable_paging
        
    
        pushl %ebx
        call _kernel_main
    
        cli
    loop:
        hlt
        jmp loop
    
    /* Load GDT and modify segment registers */
    load_gdt:
        pushl $_gdt
        pushw _gdt_limit

        lgdt (%esp)

        pop %ax
        pop %eax

        /*  
            Segment registers store segment selector

            modify CS to 0x08(0000000000001000)
            Index: 1                        Point to the second segment descriptor
            Table indicator: 0              GDT
            Requested privileged level: 0   requested DPL = 0

            modify other segment registers to 0x10(0000000000010000)
            Index: 2                        Point to the third segment descriptor
            Table indicator: 0              GDT
            Requested privileged level: 0   requested DPL = 0
        */

        ljmp $0x08, $_after_lgdt    /* modify CS by jmp instruction */

        _after_lgdt:
            movl $0x10, %eax
            
            movw %ax, %ds
            movw %ax, %es
            movw %ax, %fs
            movw %ax, %gs
            movw %ax, %ss

        ret

    load_idt:
        pushl $_idt
        pushw _idt_limit

        lidt (%esp)

        pop %ax
        pop %eax
        xor %eax, %eax

        ret
        
    enable_paging:
        /* TODO */

        ret