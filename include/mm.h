#ifndef    _MM_H
#define    _MM_H

#define PAGE_SHIFT             12
#define TABLE_SHIFT             9
#define SECTION_SHIFT            (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE               (1 << PAGE_SHIFT)    
#define SECTION_SIZE            (1 << SECTION_SHIFT)    

#define LOW_MEMORY                  (2 * SECTION_SIZE)

#define T0_STK (void *)(LOW_MEMORY - PAGE_SIZE)
#define T1_STK (void *)(T0_STK - PAGE_SIZE)
#define T2_STK (void *)(T1_STK - PAGE_SIZE)

#ifndef __ASSEMBLER__

void memzero(unsigned long src, unsigned long n);

#endif

#endif  /*_MM_H */
