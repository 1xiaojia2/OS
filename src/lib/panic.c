#include <kdebug.h>
#include <stdio.h>


void panic_spin(char* filename, int line, const char* func, const char* condition){
    printf("!!!!!!!!!ERROR!!!!!!!!!!!!\n");
    printf("Filename: %s\n", filename);
    printf("Line: %d\n", line);
    printf("Function: %s\n", func);
    printf("Condition: %s\n", condition);
    while (1);
}