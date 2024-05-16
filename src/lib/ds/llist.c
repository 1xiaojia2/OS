#include <ds/dlist.h>
#include <stddef.h>

void llist_init(llist *list){
    // lock_init(&list->lock);
    list->header.next = NULL;
}
void llist_remove(llist * plist, llist_node *node){

}
void llist_push(llist * plist, llist_node *node){
    node->next = plist->header.next;
    plist->header.next = node;
}
llist_node *llist_pop(llist * plist, llist_node *node){
    llist_node *delete_node = plist->header.next;
    plist->header.next = delete_node->next;
    return delete_node;
}