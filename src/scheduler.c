#include "thread.h"
#include "kernel.h"
#include "mini_uart.h"

__kdata static int cur_thrd = -1;
__kdata static int thrd_count = 0;
__kdata static struct thrd thrd_tbl[TASK_NUM];

__kernel int get_tid()
{
    return cur_thrd;
}

__kernel static int algorithm(int last_tsk)
{
    return (last_tsk + 1) % TASK_NUM;
}

__kernel void *scheduler(void *last_stk)
{
    cur_thrd = algorithm (cur_thrd);
    uart_send_string ("Next thread is thread ");
    uart_send (cur_thrd + '0');
    uart_send_string ("\r\n");
    return thrd_tbl[cur_thrd].sp;
}

__kernel static void init_thread(long *sp, long arg1, void (*fi)())
{
    sp[0] = 0; // x1, second argument
    sp[1] = arg1; // x0, fist argument
    sp[2] = 0;  // fp
    sp[3] = (long)fi; // lr, fist instruction
}

__kernel void load_tsk(void (*func)(), void *sp)
{
    thrd_tbl[thrd_count].sp = sp - 32;
    init_thread (thrd_tbl[thrd_count].sp, thrd_count, func);
    thrd_count++;
}

/*
__init void init_scheduler()
{
    void (*fst_ins)[TASK_NUM];
    cur_thr = 0;
    thr_stk[0] = T0_SB - 32;
    thr_stk[1] = T1_SB - 32;
    thr_stk[2] = T2_SB - 32;
    fst_ins[0] = t1;
    fst_ins[1] = t1;
    fst_ins[2] = t2;
    for (int i=0; i<TASK_NUM; i++)
        init_thread(thr_stk[i], i, fst_ins[i]);
}
*/
