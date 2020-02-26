#include "thread.h"
#include "kernel.h"
#include "mini_uart.h"
#include "iolib.h"
#include "debug.h"

__kdata static int cur_prc = 0;
__kdata static int prc_count = 0;
__kdata static struct prc prc_tbl[TASK_NUM];

__kernel int get_pid()
{
    return cur_prc;
}

__kernel static int algorithm(const int last_tsk)
{
    return (last_tsk + 1) % TASK_NUM;
}

__kernel int scheduler(const void *last_stk)
{
    dbg ("\n=== scheduler ===\n");
    dbg ("Process %d, last stack %x\n", cur_prc, last_stk);
    prc_tbl[cur_prc].sp = last_stk;
    cur_prc = algorithm (cur_prc);
    dbg ("Next process %d, load stack @ %x\n", cur_prc, prc_tbl[cur_prc].sp);
    dbg ("\n=================\n");
    return cur_prc;
}

__kernel void *reload(const int cur_prc)
{
    return prc_tbl[cur_prc].sp;
}

__kernel static void init_process(long * const sp, const long arg1, const void (*fi)())
{
    sp[0] = 0; // x1, second argument
    sp[1] = arg1; // x0, fist argument
    sp[2] = 0;  // fp
    sp[3] = (long)fi; // lr, fist instruction
    dbg ("pre-stk dump");
    // mem_dump (sp, 4 * sizeof(long));
}

__kernel void load_tsk(const void (*func)(), const void * const sp)
{
    prc_tbl[prc_count].sp = sp - 32;
    init_process (prc_tbl[prc_count].sp, prc_count, func);
    dbg ("\tProcess %d loaded, fi %x, stk %x\n", prc_count, func, sp);
    dbg ("prc_tbl dump");
    // mem_dump (prc_tbl, sizeof(prc_tbl));
    prc_count++;
}
