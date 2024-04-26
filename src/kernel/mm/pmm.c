#include <kernel/memory.h>
#include <kernel/syslog.h>
#include <kernel/vga.h>
#include <string.h>


static uint32_t bitmap[1024 * 1024 / BITMAP_GRAN];
static uint32_t pre_alloc_base;

static uint32_t mem_lower;
static uint32_t mem_upper;

static uint32_t total_page;
static uint32_t free_page;

void pmm_init(unsigned address){
    
    parse_mbi(address);

    total_page = END_PAGE(mem_upper);
    free_page = total_page;
    
    // Mark kernel binary location as occupied.
    bitmap_set_from_to(kernel_start, kernel_end, USED);

}

void *pm_alloc_the_page(uint32_t base){
    base |= ~0xFFF;
    if(bitmap_get(base)){
        printk(MEMORY, ERROR, "Page[%d] is occupied by other process.", base >> 12);
        return NULL;
    }
    return (void *)base;
}

void *pm_alloc(){

    if(free_page == 0){
        printk(MEMORY, ERROR, "No avalible memory.");
        return NULL;
    }

    size_t base;
    for (base = pre_alloc_base; base < (total_page << 12); base += 4096)
        if(bitmap_get(base) == FREE) {
            bitmap_set(base, USED);
            pre_alloc_base = base;
            return (void *)base;
        }

    for (base = 0; base < pre_alloc_base; base += 4096)
        if(bitmap_get(base) == FREE) {
            bitmap_set(base, USED);
            pre_alloc_base = base;
            return (void *)base;
        }
}

void pm_free(void *address){
    bitmap_set((uint32_t)address, FREE);
}

bool bitmap_get(uint32_t pa){
    uint32_t pp = START_PAGE(pa);
    return (bitmap[pp/BITMAP_GRAN] >> (pp%BITMAP_GRAN)) & 1;
}

void bitmap_set(uint32_t pa, bool flag){
    uint32_t pp = START_PAGE(pa);
    
    if(!(bitmap_get(pa) ^ flag)){
        printk(MEMORY, WARN, "[0x%x] is already occupied/free.", pa);
        return ;
    }
    
    uint32_t index = pp / BITMAP_GRAN;
    uint32_t offset = pp % BITMAP_GRAN;

    uint32_t num = ~(1 << offset);
    num = num & bitmap[index];
    num += flag << offset;
    bitmap[index] = num;

    free_page = flag == USED ? free_page-1 : free_page+1;
}

void bitmap_set_chunk(uint32_t base, uint32_t length, bool flag){
    
    /**
     * TODO:
     *  Optimizing algorithom
    */
   size_t count = START_PAGE(length);
    for (size_t i = 0; i < count; i++)
        bitmap_set(base + i * 4096, flag);
    
}
void bitmap_set_from_to(uint32_t from, uint32_t to, bool flag){
    for (size_t i = from; i < to + 4095; i += 4096)
        bitmap_set(i, flag);
}

void parse_mbi(unsigned address){
    address += KERNEL_BASE;
    struct multiboot_tag *tag;

    for (tag = (struct multiboot_tag *) (address + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                       + ((tag->size + 7) & ~7)))
    {
      switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
        //   printk (GRUB, INFO, "Boot loader name = %s",
        //           ((struct multiboot_tag_string *) tag)->string);
          break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
          mem_lower = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
          mem_upper = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper + 0x400;
          mem_lower *= 1024;
          mem_upper *= 1024;
        //   printk (GRUB, INFO, "mem_lower = 0x%p, mem_upper = 0x%x.", mem_lower, mem_upper);
          break;
        case MULTIBOOT_TAG_TYPE_MMAP:
          {
            multiboot_memory_map_t *mmap;
            // printk (GRUB, INFO, "mmap\n");
            for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
                 (multiboot_uint8_t *) mmap 
                   < (multiboot_uint8_t *) tag + tag->size;
                 mmap = (multiboot_memory_map_t *) 
                   ((unsigned long) mmap
                    + ((struct multiboot_tag_mmap *) tag)->entry_size)){
                uint32_t addr = (unsigned) (mmap->addr & 0xffffffff);
                uint32_t length = (unsigned) (mmap->len & 0xffffffff);
            //   printk (GRUB, INFO, " base_addr = 0x%x,"
            //           " length = 0x%x, type = 0x%x",
            //           addr,
            //           length,
            //           (unsigned) mmap->type);
                if(mmap->type == 1 && addr != 0)
                    bitmap_set_from_to(addr, addr + length, FREE);
            }
          }
          break;
        }

    }
}