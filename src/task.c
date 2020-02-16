#include "mini_uart.h"
#include "task.h"
#include "kernel.h"

__t1 void t1(int n)
{
    while(1){
        uart_send_string ("This is task one @ thread ");
        uart_send (n + '0');
        uart_send_string ("\n\r");
        uart_recv ();
        _release ();
    }
}

__t2 void t2(int n)
{
    while(1){
        uart_send_string ("This is task two @ thread ");
        uart_send (n + '0');
        uart_send_string ("\n\r");
        uart_recv ();
        _release ();
    }
}
