#ifndef _TASK_H_
#define _TASK_H_

#define __t1 __attribute__((section(".text.t1")))
#define __t2 __attribute__((section(".text.t2")))

void t1(int);
void t2(int);

#endif
