#include "mini_uart.h"
#include "memctl.h"
#include "va_arg.h"

#define TYPE_NUN 3

static char io_inited = 0;
static char in_buf;
static int baud_rate = BAUD_RATE;

void set_io_baud_rate(int rate)
{
    baud_rate = rate;
}

static void io_init()
{
    uart_init (baud_rate);
    io_inited = 1;
}

int i2s(int src, char *dis)
{
    int len;

    len = 0;

    do {
        dis[len++] = ((src % 10) & 0xff)+ '0';
        src /= 10;
    } while (src);

    return len;
}

int prt_int(char *arg)
{
    int num;
    int len;
    char buf[5];

    num = 0;
    len = 0;

    mem_cpy (arg, &num, sizeof(int));
    len = i2s (num, buf);

    for (int i=len-1; i>=0; i--) {
        uart_send (buf[i]);
    }

    return len;
}

void send_hex(char c)
{
    switch (c) {
        case 0 ... 9:
            uart_send ('0' + c);
        break;
        case 10 ... 15:
            uart_send ('A' + c - 10);
        break;
    }
}

int i2h(int src, char *dis)
{
    int len;

    len = 0;

    do {
        dis[len++] = src & 0xf;
        src >>= 4;
    } while (src);

    return len;
}

int prt_hex(char *arg)
{
    char buf[16];
    int i;
    unsigned int val;
    int ret;

    val = *(unsigned int *)arg;

    ret = i2h (val, buf);

    for (i = ret - 1; i>=0; i--) {
        send_hex (buf[i]);
    }

    return ret;
}

static int prt_parser(const char **c, void *arg)
{
    int len;
    switch (**c) {
        case 'd':
            len = prt_int (arg);
        break;
        case 'l':
            len = 8;
        break;
        case 'x':
            len = uart_send_string ("0x");
            len += prt_hex (arg);
        break;
    }
    return len;
}

int _printf(int _pad1, int _pad2, int _pad3, int _pad4, int _pad5, int _pad6, int _pad7, int _pad8,const char *s, ...)
{
    int ret;
    void *arg_ptr;

    ret = 0;
    arg_ptr = get_va_head (s);

    if (!io_inited)
        io_init ();

    while (*s != '\0') {
        switch (*s) {
            case '%':
                s++;
                ret += prt_parser (&s, arg_ptr);
                next_va (arg_ptr);
            break;
            case '\n':
                uart_send ('\n');
                uart_send ('\r');
                ret++;
            break;
            default:
                uart_send (*s);
                ret++;
            break;
        }
        s++;
    }
    return ret;
}

// TODO scanf get interger and hex
char is_end(char c)
{
    return ' ' == c || '\r' == c;
}

char is_num(char c)
{
    return '0' >= c || '9' <= c;
}

int get_int(int *arg)
{
    char c;
    int num;
     
    num = 0;

    while (1) {
        c = uart_recv ();
        if (is_end (c))
            break;
        if (is_num (c))
            return -1;
        num *= 10;
        num += c - '0';
    }
    *arg = num;
    return 0;
}

int get_hex(int *ard)
{
    return 0;
}

int get_parser(const char **c, void *arg)
{
    int ret;

    ret = 0;

    switch (**c) {
        case 'd':
            get_int (arg);
        break;
        case 'x':
            get_hex (arg);
        break;
    }
    return ret;
}

int _scanf(int _pad1, int _pad2, int _pad3, int _pad4, int _pad5, int _pad6, int _pad7, int _pad8, const char *s, ...)
{
    int i;
    int ret;
    char val;
    void *arg_ptr;
    
    i = 0;
    ret = 0;
    arg_ptr = get_va_head (s);

    if (!io_inited) 
        io_init ();

    while (*s != '\0') {
        switch (*s) {
            case '%':
                get_parser (&s, arg_ptr);
            break;
            default:
                val = uart_recv ();
                if (val != *s)
                    return -1;
            break;   
        }
        s++;
    }

    return ret;
}
