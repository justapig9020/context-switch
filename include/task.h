#ifndef _TASK_H_
#define _TASK_H_

#define __func1 __attribute__((section(".text.func1")))
#define __func2 __attribute__((section(".text.func2")))

void func1(int);
void func2(int);

#endif
