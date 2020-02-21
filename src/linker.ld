SECTIONS
{
    .text.boot : { *(.text.boot) }
    .text.init : { *(.text.init) }
    .text.kernel : { *(.text) }
    .text.func1 : { *(.text.func1) }
    .text.func2 : { *(.text.func2) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .data.kernel : { *(.data.kernel) }
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) } 
    bss_end = .;
}
