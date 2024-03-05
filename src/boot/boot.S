#include <kernel/multiboot.h>

#define STACK_SIZE  0x4000

.section .multiboot
    .align  8
    multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_ARCHITECTURE_I386
        .long   multiboot_header_end - multiboot_header
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_ARCHITECTURE_I386 + multiboot_header_end - multiboot_header)
 
    multiboot_header_tag_end:
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

    enable_paging:
        /* 32-Bit paging
        CR0.PG = 1
        CR4.PAE = 0
        upper 20 bits of CR3 stores the address of page derictory

        */
        
    
    pushl %ebx
    call _kernel_main
        cli
    loop:
        hlt
        jmp loop
