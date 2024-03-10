#include "multiboot.h"

.extern setup, kernel_init
.global _start
.global boot_page_directory

.section .multiboot, "a"
.align  MULTIBOOT_HEADER_ALIGN
multiboot_header:
    .long   MULTIBOOT_HEADER_MAGIC
    .long   MULTIBOOT_HEADER_ARCHITECTURE_I386
    .long   HEADER_LENGTH(multiboot_header, multiboot_header_end)
    .long   CHECKSUM(MULTIBOOT_HEADER_MAGIC, MULTIBOOT_HEADER_ARCHITECTURE_I386, HEADER_LENGTH(multiboot_header, multiboot_header_end))

.align  MULTIBOOT_HEADER_ALIGN
tag_information_request:
    .short  MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST
    .short  0
    .long   tag_information_request_end - tag_information_request
    .long   MULTIBOOT_TAG_TYPE_MMAP
tag_information_request_end:

.align  MULTIBOOT_HEADER_ALIGN
multiboot_header_tag_end:   
    .short MULTIBOOT_HEADER_TAG_END
    .short 0
    .long 8
multiboot_header_end:


.section .boot.bss, "aw", @nobits    
.align  16
.skip   STACK_SIZE
stack_top:

.align 4096
boot_page_directory:
    .skip 4096

.section .boot.text, "ax"
_start:

    # Identity mapping for first 8 MiB.
    movl $(0 << 22 | 0x83), boot_page_directory - 0xC0000000 + 0 * 4
    movl $(1 << 22 | 0x83), boot_page_directory - 0xC0000000 + 1 * 4

    # Map 8 MiB starting at 0xC0000000 to 0.
    movl $(0 << 22 | 0x83), boot_page_directory - 0xC0000000 + 768 * 4
    movl $(1 << 22 | 0x83), boot_page_directory - 0xC0000000 + 769 * 4
    
    movl $(boot_page_directory - 0xC0000000), %ecx
    movl %ecx, %cr3

    # Enable PSE.
    movl %cr4, %ecx
    orl $0x10, %ecx
    movl %ecx, %cr4
    
    movl %cr0, %ecx
    orl $0x80000000, %ecx
    movl %ecx, %cr0

    lea higher_half, %ecx
    jmp *%ecx

.section .text
higher_half:

    movl $stack_top, %esp 
    pushl %ebx
    
    call setup

    call kernel_init

    cli
    cy:
        hlt
        jmp cy
