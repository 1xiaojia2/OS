#ifndef _DLIST_H
#define _DLIST_H
#include <stdbool.h>

#define offset(struct_type,member) (int)(&((struct_type*)0)->member) 

#define elem2entry(struct_type, struct_member_name, elem_ptr) \ 
    (struct_type*)((int)elem_ptr - offset(struct_type, struct_member_name)) 

struct dlist_elem { 
    struct dlist_elem* prev;
    struct dlist_elem* next;
}; 

struct dlist { 
    struct dlist_elem head; 
    struct dlist_elem tail; 
}; 

typedef bool (function)(struct dlist_elem*, int arg); 

/**
 * @brief Init double linked list.
*/
void dlist_init (struct dlist* list); 

/**
 * @brief Insert 'elem' before 'before'.
*/
void dlist_insert_before(struct dlist_elem* before, struct dlist_elem* elem); 

void dlist_iterate(struct dlist* plist); 

/**
 * @brief Queue function. Insert 'elem' at the end of 'plist'.
*/
void dlist_append(struct dlist* plist, struct dlist_elem* elem); 

/**
 * @brief Remove 'pelem'.
*/
void dlist_remove(struct dlist_elem* pelem); 

void dlist_push(struct dlist* plist, struct dlist_elem* elem); 

struct dlist_elem* dlist_pop(struct dlist* plist); 

bool dlist_is_empty(struct dlist* plist); 

unsigned int dlist_len(struct dlist* plist); 

struct dlist_elem* list_traversal(struct dlist* plist, function func, int arg); 

bool dlist_elem_find(struct dlist* plist, struct dlist_elem* obj_elem); 

#endif