#ifndef _IOLIB_H_
#define _IOLIB_H_a

#define printf(a, ...) print(0, 0, 0, 0, 0, 0, 0, 0, a, ##__VA_ARGS__)

int print (int, int, int, int, int, int, int, int, char*, ...);

#endif
