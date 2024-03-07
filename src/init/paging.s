.section .text
.global _paging_fulsh
    _paging_fulsh:

        movl 4(%esp), %ecx
        movl %ecx, %cr3
        
        movl %cr4, %ecx
        or $0x10, %ecx
        movl %ecx, %cr4

        movl %cr0, %ecx
        or $0x80000000, %ecx
        movl %ecx, %cr0
        ret



    
        