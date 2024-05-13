#include <ds/dlist.h>
#include <stddef.h>
#include <asm/cpu.h>

void dlist_init(struct dlist* list){
    list->head.prev = NULL; 
    list->head.next = &list->tail; 
    list->tail.prev = &list->head; 
    list->tail.next = NULL;
}

void dlist_insert_before(struct dlist_elem* before, struct dlist_elem* elem){

    before->prev->next = elem; 
    elem->prev = before->prev; 
    elem->next = before; 
    before->prev = elem;

}

void dlist_iterate(struct dlist* plist){

}

void dlist_append(struct dlist* plist, struct dlist_elem* elem){
    dlist_insert_before(&plist->tail, elem);
}

void dlist_remove(struct dlist_elem* pelem){
    pelem->prev->next = pelem->next; 
    pelem->next->prev = pelem->prev;
}

void dlist_push(struct dlist* plist, struct dlist_elem* elem){
    dlist_insert_before(plist->head.next, elem);
}
struct dlist_elem* list_pop(struct dlist* plist){
    struct list_elem* elem = plist->head.next; 
    dlist_remove(elem); 
    return elem;
}

bool dlist_is_empty(struct dlist* plist){
    return (plist->head.next == &plist->tail ? true : false); 
}

unsigned int dlist_len(struct dlist* plist){
    struct dlist_elem* elem = plist->head.next; 
    unsigned int length = 0; 
    while (elem != &plist->tail) { 
        length++; 
        elem = elem->next; 
    } 
    return length; 
}

struct dlist_elem* dlist_traversal(struct dlist* plist, function func, int arg){
    struct dlist_elem* elem = plist->head.next;
    if (dlist_is_empty(plist)) return NULL; 
    while (elem != &plist->tail) { 
    if (func(elem, arg)) return elem; 
        elem = elem->next; 
    } 
    return NULL; 
}

bool dlist_elem_find(struct dlist* plist, struct dlist_elem* obj_elem){
    struct dlist_elem* elem = plist->head.next; 
    while (elem != &plist->tail) { 
        if (elem == obj_elem)
            return true; 
        elem = elem->next; 
    } 
    return false;
}

struct dlist_elem* dlist_pop(struct dlist* plist){
    struct dlist_elem* elem = plist->head.next; 
    dlist_remove(elem); 
    return elem;
}