#define MULTIBOOT_HEADER_MAGIC                  0xE85250D6
#define MULTIBOOT_HEADER_ARCHITECTURE_I386      0
#define MULTIBOOT_HEADER_ALIGN                  8
#define HEADER_LENGTH(from, to)                 (to - from)
#define CHECKSUM(magic, arch, length)           -(magic + arch + length)

#define STACK_SIZE                              0x4000



.section .multiboot
.align  MULTIBOOT_HEADER_ALIGN
    multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_ARCHITECTURE_I386
        .long   HEADER_LENGTH(multiboot_header, multiboot_header_end)
        .long   CHECKSUM(MULTIBOOT_HEADER_MAGIC, MULTIBOOT_HEADER_ARCHITECTURE_I386, HEADER_LENGTH(multiboot_header, multiboot_header_end))
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

        pushl %ebx
        call _kernel_main

        cli
    loop:
        hlt
        jmp loop
