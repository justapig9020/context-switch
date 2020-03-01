#include "iolib.h"

void mem_dump(const char *addr, unsigned int sz)
{
    char c;
    printf ("\n\r=== mem dump ===\n\r");
    for (int i=0; i<sz; i++) {
        if (0 == (i&0xf)) {
            printf ("\n");
        }else if (0 == (i&0x7)) {
            uart_send (' ');
        }
        c = (addr[i] >> 4) & 0xf;
        printf ("%c", c + '0');
        c = (addr[i] & 0xf);
        printf ("%c", c + '0');
    }
    printf ("\n\r======\n\r");
}

void mem_cpy(const void *src, void *dis, int len)
{
    for (int i=0; i<len; i++)
        ((char *)dis)[i] = ((char *)src)[i];
}
