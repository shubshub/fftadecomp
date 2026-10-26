#include "ffta.h"

/* 0x080CBD34..0x080CBDC0: 140 bytes, including the literal pool. */
extern s32 func_080CA7A4(u16 id, u32 field);
extern u8 func_080CB1F4(u16 id);

u8 func_080CBD34(u16 id)
{
    if (func_080CA7A4(id, 6) == 3)
        return 0;
    if (func_080CA7A4(id, 6) == 4)
        return 1;
    if (func_080CB1F4(id))
        return 2;
    if (func_080CA7A4(id, 3) == 20)
        return 3;
    if (func_080CA7A4(id, 3) == 29 ||
        func_080CA7A4(id, 6) == 5 ||
        func_080CA7A4(id, 3) == 28)
        return 4;
    if ((u16)(id - 362) <= 13)
        return 5;
    return 255;
}
