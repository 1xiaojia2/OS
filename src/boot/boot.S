#include "multiboot.h"

#define KERNEL_BASE 0xC0000000
#define BOOT_STACK_SIZE  0x4000

.extern setup, kernel_init
.extern page_directory, kernel_page_tables
.global _start
.global boot_stack_top

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

#--------------------------------------------------

.section .boot.text, "ax"
_start:

    movl $(boot_stack_top - KERNEL_BASE), %esp
    pushl %ebx

    pushl $(kernel_page_tables - KERNEL_BASE)
    pushl $(page_directory - KERNEL_BASE)

    call hhk

    addl $0x08, %esp
    
    movl $(page_directory - KERNEL_BASE), %ecx
    movl %ecx, %cr3
    
    movl %cr0, %ecx
    orl $0x80000000, %ecx
    movl %ecx, %cr0

    pop %ebx

    lea high_half, %ecx
    jmp *%ecx


.section .text
high_half:
    /* 
    * By now, we have entirly entered higher half kernel.
    * We should first setup necessery data structures for x86. 
    */

    /* Reload esp because now we are in hhk. */
    movl $boot_stack_top, %esp
    pushl %ebx

    call setup
    
    /* Time to enter kernel world. */
    call kernel_init
    CLI
    cy:
        hlt
        jmp cy


.section .boot.bss, "aw", @nobits
.align  16
.skip   BOOT_STACK_SIZE
boot_stack_top: