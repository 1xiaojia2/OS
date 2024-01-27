#include <arch/i386/gdt.h>
#include <LeeOS/tty/tty.h>


void _kernel_initialize(){
    _gdt_init();
    
}


void _kernel_main(){
    tty_initialize();
    
    tty_put_str("Hello, kernel world!\n");
    
}