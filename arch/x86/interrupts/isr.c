#include <arch/x86/interrupts/idt.h>
#include <libc/stdio.h>

static const char* exception_messages[] = {
    "Divide Error", 
    "Debug Exception", 
    "Non-maskable Interrupt", 
    "Breakpoint", 
    "Overflow", 
    "Bound Range Exceeded", 
    "Invalid Opcode", 
    "Device Not Available", 
    "Double Fault", 
    "Coprocessor Segment Overrun", 
    "Invalid TSS", 
    "Segment Not Present", 
    "Stack-Segment Fault", 
    "General Protection Fault", 
    "Page Fault", 
    "Reserved", 
    "x87 FPU Floating-Point Error", 
    "Alignment Check", 
    "Machine Check", 
    "SIMD Floating-Point Exception", 
    "Virtualization Exception", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Reserved", 
    "Security Exception"
};


void isr0(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr1(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}

void isr2(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr3(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr4(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr5(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr6(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr7(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr8(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr9(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr10(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr11(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr12(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr13(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr14(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr15(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr16(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr17(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr18(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr19(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}

void isr20(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr21(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr22(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr23(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr24(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr25(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr26(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr27(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr28(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr29(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr30(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}
void isr31(struct isr_regs regs){
    printf("ERROR: %s\n", exception_messages[regs.vector]);
}