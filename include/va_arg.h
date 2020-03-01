#ifndef _VA_ARG_H_
#define _VA_ARG_H_

#define get_va_head(s) ((void *)(((char *)&s) + sizeof(void *)))
#define next_va(s) (s = ((void *)(((char *)s)+sizeof(void *))))

#endif
