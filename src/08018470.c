#include "ffta.h"

/* 0x08018470..0x08018484: 20 bytes. */
u8 func_08018470(u8 value)
{
    u8 result = 0;

    if (value == 9)
        result = 1;
    return result;
}
