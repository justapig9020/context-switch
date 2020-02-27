#include "mini_uart.h"
#include "iolib.h"
#include "kernel.h"
#include "process.h"
#include "task.h"
#include "mm.h"

__init void init_kernel(void)
{
    int n;
    int ret;
    void *stk_ptr;

    stk_ptr = (void *)LOW_MEMORY;
    ret = printf ("\n=== Hello, world! ===\n");
    printf ("len: %d\n", ret);

    stk_ptr -= PAGE_SIZE;
    load_tsk (func1, stk_ptr);
    printf ("Process0 loaded, fi@%x, stk@%x!\n", func1, stk_ptr);

    stk_ptr -= PAGE_SIZE;
    load_tsk (func1, stk_ptr);
    printf ("Process1 loaded, fi@%x, stk@%x!\n", func1, stk_ptr);

    stk_ptr -= PAGE_SIZE;
    load_tsk (func2, stk_ptr);
    printf ("Process2 loaded, fi@%x, stk@%x!\n", func2, stk_ptr);

    _start_kernel ();
}
