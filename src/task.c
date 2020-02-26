#include "mini_uart.h"
#include "task.h"
#include "kernel.h"
#include "iolib.h"

static void delay()
{
    for (unsigned int i=0; i<0xfffff; i++);
}

__func1 void func1(int n)
{
    int i;
    i = 0;
    while(1){
        printf ("%d : This is func1 @ Process %d !!!!\n", i++, n);
        delay ();
        _release ();
    }
}

__func2 void func2(int n)
{
    int i;
    while(1){
        printf ("%d : This is func2 @ Process %d !!!!\n", i++, n);
        delay ();
        _release ();
    }
}
