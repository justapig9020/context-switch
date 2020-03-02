#include "connect/mini_uart.h"
#include "iolib.h"
#include "kernel/kernel.h"
#include "kernel/process.h"
#include "task.h"
#include "kernel/mm.h"

__init void init_kernel(void)
{
    void *stk_ptr;

    uart_init (BAUD_RATE);
    stk_ptr = (void *)K_STK;
    printf ("\n=== Hello, world! ===\n");

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
