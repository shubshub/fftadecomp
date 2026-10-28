#include "ffta.h"

/* 080161A0..080161BA: 26 bytes. */
u16 func_080161A0(u8 x, u8 y, u8 width)
{
    return y * width + x;
}
