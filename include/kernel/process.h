#ifndef _THREAD_H_
#define _THREAD_H_

#define TASK_NUM 3

struct process
{
    void *sp;
};

int get_pid();
void scheduler(void*);
void *reload_stk();
void load_tsk(void (*)(), void *);

#endif
