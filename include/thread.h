#ifndef _THREAD_H_
#define _THREAD_H_

#define TASK_NUM 3

struct prc
{
    void *sp;
};

int get_pid();
int scheduler(void*);
void *reload(int)
void load_tsk(void (*)(), void *);

#endif
