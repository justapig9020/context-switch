#ifndef _KERNEL_H_
#define _KERNEL_H_

//#define __kernel __attribute__((section(".text.kernel")))
#define __kernel 
#define __init __attribute__((section(".text.init")))
#define __kdata __attribute__((section(".data.kernel")))

extern void _release();
extern void _start_kernel();
void init_kernel(void);

#endif
