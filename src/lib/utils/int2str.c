#include <utils.h>
#include <string.h>
#include <stdio.h>

char *uint2str(uint32_t num){
    // char str[20]; 
    // memset(str, 0, 20);
    // char *ptr = &str[sizeof(str) - 1];

    // *ptr = '\0'; 
    
    // do {
    //     *--ptr = '0' + (num % 10);
    //     num /= 10;
    // } while (num != 0);

    // return ptr;
    return u_base_cnvrsn(10, num);
}

char *int2str(int num) {
    if(num >= 0) return uint2str(num);

    /**
     * TODO: 
     *  case: num < 0
    */
}