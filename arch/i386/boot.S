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

        call _kernel_initialize      

        pushl $_gdt
        pushw _gdt_limit

        lgdt (%esp)
        
        pop %ax
        pop %eax
        xor %eax, %eax 

        ljmp $0x08, $_after_lgdt    /* modify CS */

    _after_lgdt:
        movw $0x10, %ax
        
        movw %ax, %ds
        movw %ax, %es
        movw %ax, %fs
        movw %ax, %gs
        movw %ax, %ss
        
    
        pushl %ebx
        call _kernel_main
    
        cli
    loop:
        hlt
        jmp loop
