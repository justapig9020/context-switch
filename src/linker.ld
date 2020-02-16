SECTIONS
{
    .text.boot : { *(.text.boot) }
    .text.kernel : { *(.text) }
    .text.t1 : { *(.text.t1) }
    .text.t2 : { *(.text.t2) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .data.kernel : { *(.data.kernel) }
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) } 
    bss_end = .;
}
