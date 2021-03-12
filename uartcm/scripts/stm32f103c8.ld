OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
    ROM  (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .isr_vector ORIGIN(ROM) :
    {
        KEEP(*(.isr_vector))
    } >ROM
    
    .text ALIGN(4) :
    {
        *(.text*);
    } > ROM
    
    
    .common ORIGIN(RAM) (NOLOAD) :
    {
        *(COMMON)
    } >RAM
    
    .bss ALIGN(4) (NOLOAD): {
        PROVIDE(__bss_start__ = .);
        *(.bss*)
        PROVIDE(__bss_end__ = .);
    } > RAM
    
    .data ALIGN(4):
    {
        PROVIDE(__data_start__ = .);
        *(.data*)
        PROVIDE(__data_end__ = .);
    } > RAM AT>ROM
    
    PROVIDE(__data_lma__ = LOADADDR(.data));    
    PROVIDE(__stack_top__ = ORIGIN(RAM) + LENGTH(RAM));
}
