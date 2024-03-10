.global page_directory, page_tables, mbi
.global reload_page_dir

.align 4096
.section .bss
page_tables:
    .skip 4096 * 1024
page_directory:
    .skip 4096
bitmap:
    .skip 5197 * 4

mbi:
    .skip 4096

.section .text
reload_page_dir:
    movl $page_directory, %ecx
    movl %ecx, %cr3
    ret
