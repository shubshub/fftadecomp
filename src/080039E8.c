#include "ffta.h"

/* 0x080039E8..0x08003A08: 32 bytes. */
extern u8 data_030034D1;
extern u16 data_030034D2;

void func_080039E8(u16 value, u8 mode)
{
    data_030034D1 = mode;
    data_030034D2 = value | 0x8000;
}
