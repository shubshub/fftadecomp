#include "ffta.h"

/* 0x0800C1AC..0x0800C1C8: 28 bytes / 13 instructions. */
extern void func_0800C1C8(u8 index);

void func_0800C1AC(void)
{
    u16 index;

    for (index = 0; index < 2; ++index)
        func_0800C1C8(index);
}
