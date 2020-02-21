#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "iolib.h"

#define DEBUG 0
#if DEBUG
    #define dbg(a, ...) printf(a, ##__VA_ARGS__)
#else
    #define dbg(a, ...)
#endif

#endif
