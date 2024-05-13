#ifndef _PP_INFO_H
#define _PP_INFO_H
#include <stdint.h>
#include <stdbool.h>

typedef struct shared_page_table
{
       
} shared_page_table;
 

void smm_init();
bool smm_try_to_share(uint32_t base, uint32_t pid);
void smm_unshare(uint32_t base, uint32_t pid);
/**
 * @brief   Check if the page is sharing.
 * @param address Base of the page.
 * @return If is sharing, return the address of spte, if not, return NULL.
*/
void *smm_is_sharing(uint32_t address);

#endif