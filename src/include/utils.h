#ifndef _UTILS_H
#define _UTILS_H 1
#include <stdint.h>

char *int2str(int num);
char *uint2str(uint32_t num);
uint32_t abs(int num);
char *dec2hex(int num);
char *u_dec2hex(uint32_t num);

char *u_base_cnvrsn(uint32_t to, uint32_t num);

#endif
