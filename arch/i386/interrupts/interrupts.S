.macro _isr_template vector, no_error_code=1
    .global _asm_isr\vector
    .type _asm_isr\vector, @function
    _asm_isr\vector :
        .if \no_error_code
            pushl $0
        .endif
        pushl $\vector
        jmp isr_wrapper
.endm


.section .text
    
    _isr_template 0
    /*TODO:
        insert more templates
    */
    
    isr_wrapper:

        call interrupt_handler
        
        addl $0x08, %esp

        iret

