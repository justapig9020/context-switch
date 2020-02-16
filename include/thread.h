#ifndef _THREAD_H_
#define _THREAD_H_

#define TASK_NUM 3

struct thrd 
{
    void *sp;
};

int get_tid();
void *scheduler(void*);
void load_tsk(void (*)(), void *);

#endif
