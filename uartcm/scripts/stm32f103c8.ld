OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
    rom(rx):  ORIGIN = 0x08000000, LENGTH = 64K
    ram(rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS { 

   .isr_vector ORIGIN(rom): { 
       KEEP(*(.isr_vector)) 
   } > rom 

   .text: ALIGN(4) { 
       *(.text*) 
   } > rom

   .common ORIGIN(ram)(NOLOAD): { 
       *(COMMON) 
   } > ram

   .bss ALIGN(4) (NOLOAD): {
        PROVIDE(__bss_start__ = .);
        *(.bss*)
        PROVIDE(__bss_end__ = .);
    } > ram

    .data ALIGN(4): {
        PROVIDE(__data_start__ = .);
        *(.data*)
        PROVIDE(__data_end__ = .);
    } > ram AT > rom

    PROVIDE(__data_lma__ = LOADADDR(.data));
    PROVIDE(__stack_top = ORIGIN(ram) + LENGTH(ram));
}
