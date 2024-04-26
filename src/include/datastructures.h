#ifndef _DATASTRUC_H
#define _DATASTRUC_H    1
#include <stdint.h>

struct linked_list
{
    int data;
    uintptr_t next;
};

typedef struct linked_list llist;


#endif