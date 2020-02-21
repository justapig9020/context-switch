#include "mini_uart.h"
#include "task.h"
#include "kernel.h"
#include "iolib.h"

static void delay()
{
    for (int i=0; i<100000; i++);
}

__func1 void func1(int n)
{
    char c;
    int i;
    i = 0;
    while(1){
        printf ("%d : This is func1 @ thread %d !!!!\n", i++, n);
        delay ();
        _release ();
    }
}

__func2 void func2(int n)
{
    char c;
    int i;
    while(1){
        printf ("%d : This is func2 @ thread %d !!!!\n", i++, n);
        delay ();
        _release ();
    }
}
