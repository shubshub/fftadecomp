#include "ffta.h"

/* 0x08003934 - 28 bytes. Set the byte value and reset the following halfword. */
extern u8 data_030034D1;
extern u16 data_030034D2;

void func_08003934(u8 value)
{
    data_030034D1 = value;
    data_030034D2 = 0xFFFE;
}
