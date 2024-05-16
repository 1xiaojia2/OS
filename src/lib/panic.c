#include <kdebug.h>
#include <kernel/tty.h>
#include <asm/cpu.h>

void panic_spin(char* filename, int line, const char* func, const char* condition){
    tty_write("!!!!!!!!!ERROR!!!!!!!!!!!!\n");
    printf("Filename: %s\n", filename);
    printf("Line: %d\n", line);
    printf("func: %s\n", func);
    printf("condition: %s\n", condition);
    cli();
    for(;;);
}