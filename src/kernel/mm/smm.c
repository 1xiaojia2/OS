// #include <kernel/mm/smm.h>
// #include <stddef.h>
// #include <kernel/mm/kmalloc.h>

// shared_page_table spt;
// shared_page_table *spt_last;

// void smm_init(){
//     spt.base_refer = 0;
//     spt.pid_list = NULL;
//     spt.next = NULL;
//     spt_last = &spt;
// }



// bool smm_try_to_share(uint32_t base, uint32_t pid){
//     base &= 0xFFFFC000;
//     shared_page_table *spte = smm_is_sharing(base);
//     spt_pid_llist *pid_list_entry;
//     if(spte==NULL){
//         if((spte = (shared_page_table *)kmalloc(sizeof(shared_page_table *))) == NULL) 
//             return false;
//         spte->base_refer = base;

//         if((pid_list_entry = kmalloc(sizeof(spt_pid_llist *))) == NULL)
//             return false;
//         pid_list_entry->next = spte->pid_list->next;
//         spte->pid_list = pid_list_entry;

//         spte->pid_list->pid = pid;
//         spte->next = spt_last->next;
//         spt_last->next = spte;
//         spt_last = spte;
//     }
//     else{
//         if((spte->base_refer & ~0xFFFFC000) == ~0xFFFFC000) return false;
        
//         if((pid_list_entry = kmalloc(sizeof(spt_pid_llist *))) == NULL)
//             return false;
//         pid_list_entry->next = spte->pid_list->next;
//         spte->pid_list = pid_list_entry;

//         spte->base_refer++;
//         spte->pid_list = pid_list_entry;
//     }
//     return true;
// }
// void smm_unshare(uint32_t base, uint32_t pid){
//     base &= 0xFFFFC000;
//     shared_page_table *spte = smm_is_sharing(base);
//     if(spte == NULL) return ;
//     spte->base_refer--;
//     if((spte->base_refer & ~0xFFFFC000) == 0){
        
//     }
// }

// void *smm_is_sharing(uint32_t address){

// }