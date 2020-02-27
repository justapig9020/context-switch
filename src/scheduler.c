#include "process.h"
#include "kernel.h"
#include "mini_uart.h"
#include "iolib.h"
#include "debug.h"

static int __kdata cur_pid = 0;
static int __kdata prc_num = 0;
static struct process __kdata prc_tbl[TASK_NUM];

int __kernel get_pid()
{
    return cur_pid;
}

static int __kernel algorithm(int last_tsk)
{
    return (last_tsk + 1) % TASK_NUM;
}

void __kernel scheduler(void *last_stk)
{
    dbg ("\n=== scheduler ===\n");
    dbg ("Process %d, last stack %x\n", cur_pid, last_stk);

    prc_tbl[cur_pid].sp = last_stk;
    cur_pid = algorithm (cur_pid);

    dbg ("Next process %d, load stack @ %x\n", cur_pid, prc_tbl[cur_pid].sp);
    dbg ("\n=================\n");
}

void __kernel *reload_stk()
{
    dbg ("reloading, sp: %x\n", prc_tbl[cur_pid].sp);

    return prc_tbl[cur_pid].sp;
}

static void __kernel init_process(long * sp, long arg1, void (*fi)())
{
    sp[0] = 0; // x1, second argument
    sp[1] = arg1; // x0, fist argument
    sp[2] = 0;  // fp
    sp[3] = (long)fi; // lr, fist instruction
    dbg ("pre-stk dump");
}

void __kernel load_tsk(void (*func)(), void * sp)
{
    prc_tbl[prc_num].sp = sp - 32;
    init_process (prc_tbl[prc_num].sp, prc_num, func);

    dbg ("\tProcess %d loaded, fi %x, stk %x\n", prc_num, func, sp);

    prc_num++;
}
