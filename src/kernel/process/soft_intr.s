.global soft_intr, switch_to

.section .text
soft_intr:
    
    iret

switch_to:
    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    
    movl 20(%esp), %eax
    movl %esp, (%eax)

    movl 24(%esp), %eax
    movl (%eax), %esp

    pop %ebp
    pop %ebx
    pop %edi
    pop %esi

    ret

