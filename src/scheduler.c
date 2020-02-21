#include "thread.h"
#include "kernel.h"
#include "mini_uart.h"
#include "iolib.h"
#include "debug.h"

__kdata static int cur_thrd = 0;
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
    dbg ("\n=== scheduler ===\n");
    dbg ("Process %d, last stack %x\n", cur_thrd, last_stk);
    thrd_tbl[cur_thrd].sp = last_stk;
    cur_thrd = algorithm (cur_thrd);
    dbg ("Next process %d, load stack @ %x\n", cur_thrd, thrd_tbl[cur_thrd].sp);
    dbg ("\n=================\n");
    return thrd_tbl[cur_thrd].sp;
}

__kernel static void init_process(long *sp, long arg1, void (*fi)())
{
    sp[0] = 0; // x1, second argument
    sp[1] = arg1; // x0, fist argument
    sp[2] = 0;  // fp
    sp[3] = (long)fi; // lr, fist instruction
    dbg ("pre-stk dump");
    // mem_dump (sp, 4 * sizeof(long));
}

__kernel void load_tsk(void (*func)(), void *sp)
{
    thrd_tbl[thrd_count].sp = sp - 32;
    init_process (thrd_tbl[thrd_count].sp, thrd_count, func);
    dbg ("\tProcess %d loaded, fi %x, stk %x\n", thrd_count, func, sp);
    dbg ("thrd_tbl dump");
    // mem_dump (thrd_tbl, sizeof(thrd_tbl));
    thrd_count++;
}
