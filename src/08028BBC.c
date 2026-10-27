#include "ffta.h"

/* 0x08028BBC..0x08028BDA: 30 bytes / 13 instructions. */
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);

void func_08028BBC(void)
{
    func_0802A2C0(2, 2, 26, 6);
    func_0802A370(1, 9, 14, 11);
}
