#ifndef _DS_TIRE_H
#define _DS_TIRE_HH

#include <ds/dlist.h>
#include <kernel/sync.h>
#include <stdbool.h>
typedef struct
{
    char element;
    bool is_end;
    llist children_list;
} tire_node;

typedef struct
{
    tire_node root;
    struct lock lock;
} tire;

void tire_init(tire *tree);
void tire_insert(tire tree, char *str);

#endif 