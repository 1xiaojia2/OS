ENTRY(_start)
SECTIONS {
    # 2 MiB is better, mbi can be stored below the start address of kernel
    . = 2M;

    _kernel_start = .;

    .multiboot ALIGN(4K) : ALIGN(4K){
            *(.multiboot)
    }

    .boot.text ALIGN(4K) : ALIGN(4K){
            *(.boot.text)
    }

    . += 0xC0000000;

    .text ALIGN(4K) : AT(ADDR(.text) - 0xC0000000){
            *(.text)
    }

    .data ALIGN(4K) : AT(ADDR(.data) - 0xC0000000){
            *(.data)
    }

    .rodata ALIGN(4K) : AT(ADDR(.rodata) - 0xC0000000){
            *(.rodata)
    }

    
    .bss ALIGN(4K) : AT(ADDR(.bss) - 0xC0000000){
            *(COMMON)
            *(.bss)
            *(.boot.bss)
    }

    _kernel_end = .;
    
}