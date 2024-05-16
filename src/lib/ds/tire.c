#include <ds/tire.h>
#include <kernel/mm/kmalloc.h>

void tire_init(tire *tree){
    lock_init(&tree->lock);
    tree->root.is_end = false;
    llist_init(&tree->root.children_list);

}
void tire_insert(tire tree, char *str){
    char *ptr = str;
    
    while (*ptr != '\0')
    {
        
        ptr++;
    }
    
}

tire_node *tire_next_child(tire_node *node){
    tire_node *next = NULL;
}