#include "mm.h"

.section ".text.kernel"
.globl _release
_release:
    stp x29, x30, [sp, -16]!
    stp x1, x0, [sp, -16]!
    mov x0, sp
    mov sp, #LOW_MEMORY
    mov x29, #LOW_MEMORY
    bl scheduler
_reload:
    bl reload_stk
    mov sp, x0
    ldp x1, x0, [sp], 16
    ldp x29, x30, [sp], 16
    ret 

.section ".text.init"
.globl _start_kernel
_start_kernel:
    b _reload
