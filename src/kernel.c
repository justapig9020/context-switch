#include "mini_uart.h"
#include "iolib.h"
#include "kernel.h"
#include "thread.h"
#include "task.h"
#include "mm.h"

//__init 
void init_kernel(void)
{

    uart_init (BAUD_RATE);
    printf ("hello %d, %x\n\r", 0x1234, (unsigned long)0xABCD);
    uart_send_string ("\r\n=== Hello, world! ===\r\n");
/*
    load_tsk (t1, T0_STK);
    uart_send_string ("Thread0 loaded!\r\n");

    load_tsk (t1, T1_STK);
    uart_send_string ("Thread1 loaded!\r\n");

    load_tsk (t2, T2_STK);
    uart_send_string ("Thread2 loaded!\r\n");

    _start_kernel ();
    */
}
