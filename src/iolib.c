#include "mini_uart.h"

#define TYPE_NUN 3

void prt_int(char *arg)
{
    int a;
    char buf[5];
    a = 0;
    uart_send_string ("prt_int\n\r");
    mem_dump (arg, 4);
    for (int i=0; i<4; i++) {
        a <<= 8;
        a += arg[i];
    }
    mem_dump (&a, 4);
    for (int i=4; i>=0; i--) {
        buf[i] = (a%10) + '0';
        a /= 10;
    }
    for (int i=0; i<5; i++) {
        uart_send (buf[i]);
    }
}

void send_hex(char c)
{
    switch (c) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            uart_send (c + '0');
        break;
        case 10:
            uart_send ('A');
        break;
        case 11:
            uart_send ('B');
        break;
        case 12:
            uart_send ('C');
        break;
        case 13:
            uart_send ('D');
        break;
        case 14:
            uart_send ('E');
        break;
        case 15:
            uart_send ('F');
        break;
    }
}

void mem_dump(char *addr, unsigned int sz)
{
    char c;
    uart_send_string ("\n\r=== mem dump ===\n\r");
    for (int i=0; i<sz; i++) {
        if (i%16 == 0) {
            uart_send ('\r');
            uart_send ('\n');
        }else if (i%8 == 0) {
            uart_send (' ');
        }
        c = (addr[i] >> 4) & 0xf;
        send_hex(c);
        c = (addr[i] & 0xf);
        send_hex(c);
    }
    uart_send_string ("\n\r======\n\r");
}

void send_addr(unsigned long prt)
{
    char c;
    for (int i=0; i<16; i++) {
        c = (prt & 0xf);
        prt >>= 4;
        send_hex(c);
    }
}

void prt_hex(char *arg)
{
    char buf[16];
    int o;
    for (int i=15, o=7; i>=0; o--) {
        buf[i--] = (arg[o] >> 4) & 0x0f;
        buf[i--] = arg[o] & 0x0f;
    }
    uart_send_string ("0x");
    for (int i=15; i>=0; i--) {
        send_hex (buf[i]);
    }
}

int prt_arg(char c, char *arg)
{
    int len;
    switch (c) {
        case 'd':
            len = 8;
            prt_int (arg);
        break;
        case 'l':
            len = 8;
        break;
        case 'x':
            len = 8;
            prt_hex (arg);
        break;
    }
    return len;
}

void prt_sc(char c)
{
    switch (c) {
        case 'n':
            uart_send ('\n');
            uart_send ('\r');
        break;
        case '\\':
            uart_send ('\\');
        break;
        case 'r':
            uart_send ('\n');
            uart_send ('\r');
        break;
    }
}

int print(int a, int b, int c, int d, int e, int f, int g, int h, char *s, ...)
{
    int i = 0;
    char *arg_ptr;

    arg_ptr = ((char *)&s) + sizeof(s);
    uart_send_string ("---\r\n");
    send_addr (0x1234);
    uart_send_string ("---\r\n");
    send_addr ((unsigned long)&h);
    uart_send_string ("---\r\n");
    send_addr ((unsigned long)arg_ptr);
    uart_send_string ("---\r\n");
    mem_dump (arg_ptr, 0x40);
    while (s[i] != '\0') {
        switch (s[i]) {
            case '%':
                arg_ptr += prt_arg (s[++i], arg_ptr);
            break;
            case '\\':
                prt_sc (s[++i]);
            break;
            default:
                uart_send (s[i]);
            break;
        }
        i++;
    }
    return 0;
}
