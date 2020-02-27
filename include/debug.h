#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "iolib.h"

#ifdef DEBUG
    #define dbg(a, ...) printf(a, ##__VA_ARGS__)
#else
    #define dbg(a, ...)
#endif

#endif
