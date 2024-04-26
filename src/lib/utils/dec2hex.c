#include <utils.h>

char *u_dec2hex(uint32_t num){
    // char str[32]; 
    // memset(str, 0, 32);
    // char *ptr = &str[sizeof(str) - 1];

    // *ptr = '\0'; 

    // do {
    //     int remainder = num % 16;
    //     *--ptr = remainder < 10 ?  '0' + remainder : 'a' + (remainder - 10);
    //     num /= 16;
    // } while (num != 0);
    // return ptr;
    return u_base_cnvrsn(16, num);
}

char *dec2hex(int num) {
    char str[32]; 
    memset(str, 0, 32);
    char *ptr = &str[sizeof(str) - 1];
    /**
     * TODO:
     *      signed convert
    */
    return ptr;
}