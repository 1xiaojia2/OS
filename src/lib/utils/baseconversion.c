#include <utils.h>
#include <string.h>

char *u_base_cnvrsn(uint32_t to, uint32_t num){
    char str[32]; 
    memset(str, 0, 32);
    char *ptr = &str[sizeof(str) - 1];

    *ptr = '\0'; 

    do {
        int remainder = num % to;
        *--ptr = remainder < 10 ?  '0' + remainder : 'a' + (remainder - 10);
        num /= to;
    } while (num != 0);
    return ptr;
}