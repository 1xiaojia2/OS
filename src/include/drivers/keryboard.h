#include <x86/headers.h>


typedef uint32_t kbd_sc_t;


struct kbd_event
{
    
};



void keyboard_handler(struct isr_regs *regs);

void init_keryboard();