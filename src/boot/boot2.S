#define MULTIBOOT_HEADER_MAGIC                  0xE85250D6
#define MULTIBOOT_HEADER_ARCHITECTURE_I386      0
#define HEADER_LENGTH(from, to)                 (to - from)
#define CHECKSUM(magic, arch, length)           -(magic + arch + length)
#define MULTIBOOT_HEADER_TAG_END                0

#define STACK_SIZE                              0x4000                      

.extern _kernel_start
.extern _kernel_end
.extern _kernel_main


.section .multiboot 
.align  8
    multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_ARCHITECTURE_I386
        .long   HEADER_LENGTH(multiboot_header, multiboot_header_end)
        .long   CHECKSUM(MULTIBOOT_HEADER_MAGIC, MULTIBOOT_HEADER_ARCHITECTURE_I386, HEADER_LENGTH(multiboot_header, multiboot_header_end))
    multiboot_header_tag_end:   
        .short MULTIBOOT_HEADER_TAG_END
        .short 0
        .long 8
    multiboot_header_end:


.section .boot_stack, "aw" @nobits
.align  16
    stack_bottom:
        .skip   STACK_SIZE
    stack_top:

.section .bss
.align 4096
    boot_page_directory:
        .skip 4096
    boot_page_table1:
        .skip 4096



.section .boot, "ax"
.global _start
    _start:
        


        movl %ecx, %cr3

        movl %cr4, %ecx
        or $0x10, %ecx
        movl %ecx, %cr4
        
        movl %cr0, %ecx
        or $0x80000000, %ecx
        movl %ecx, %cr0

        lea higher_half, %ecx
	    jmp *%ecx


.section .text
    higher_half:
        movl $stack_top, %esp 
        pushl %ebx
        
        call _kernel_main

        cli
        loop:
            hlt
            jmp loop
