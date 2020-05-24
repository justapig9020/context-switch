#include "mini_uart.h"
#include "iolib.h"
#include "kernel.h"
#include "thread.h"
#include "task.h"
#include "mm.h"

__init void init_kernel(void)
{

    uart_init (BAUD_RATE);
    printf ("\n=== Hello, world!! ===\n");

    load_tsk (func1, T0_STK);
    printf ("Process1 loaded, fi@%x, stk@%x!\n", func1, T0_STK);

    load_tsk (func1, T1_STK);
    printf ("Process1 loaded, fi@%x, stk@%x!\n", func1, T1_STK);

    load_tsk (func2, T2_STK);
    printf ("Process2 loaded, fi@%x, stk@%x!\n", func2, T2_STK);

    _start_kernel (T0_STK - 0x20);
}
