.section .text
.global _gdtFlush

_gdtFlush:
    movl 4(%esp), %ecx
    lgdt (%ecx)

    movw $0x10, %cx
            
    movw %cx, %ds
    movw %cx, %es
    movw %cx, %fs
    movw %cx, %gs
    movw %cx, %ss

    ljmp $0x08, $_after_lgdt
_after_lgdt:
    ret
