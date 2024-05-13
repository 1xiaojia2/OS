.global gdt_flush, idt_flush, tss_flush
.global page_directory, kernel_page_tables

.section .text
gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)
    movw $0x10, %cx
    movw %cx, %ds
    movw %cx, %es
    movw %cx, %fs
    movw %cx, %gs
    movw %cx, %ss
    ljmp $0x08, $after_lgdt
    after_lgdt:
    ret

idt_flush:
    movl 4(%esp), %eax
    lidt (%eax)
    sti
    ret

tss_flush:
    movw $0x2B, %ax
    ltr %ax
    ret


.section .bss
.align 4096
kernel_page_tables:
    .skip 4096 * 256
page_directory:
    .skip 4096