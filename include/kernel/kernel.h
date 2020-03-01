#ifndef _KERNEL_H_
#define _KERNEL_H_

#define __kernel __attribute__((section(".text.kernel")))
#define __init __attribute__((section(".text.init")))
#define __kdata __attribute__((section(".data.kernel")))

void _release();
void _start_kernel();
void init_kernel(void);

#endif