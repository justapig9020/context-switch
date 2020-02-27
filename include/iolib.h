#ifndef _IOLIB_H_
#define _IOLIB_H_

#define printf(a, ...) _printf(0, 0, 0, 0, 0, 0, 0, 0, a, ##__VA_ARGS__)
#define scanf(a, ...) _scanf(0, 0, 0, 0, 0, 0, 0, 0, a, ##__VA_ARGS__)

void set_io_baud_rate(int);
int prt_int(char *);
void send_hex(char);
int prt_hex(char *);

int _printf(int, int, int, int, int, int, int, int, const char*, ...);
int _scanf(int, int, int, int, int, int, int, int, const char*, ...);

#endif
