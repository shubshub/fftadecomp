#include "ffta.h"

/* 0x080D8B28..0x080D8B4C: 36 bytes. */
extern int func_0801BB94(s16 x, s16 y, int first, int second, int third);

int func_080D8B28(s16 x, s16 y)
{
    u16 result = func_0801BB94(x, y, 4, 0x10, 4);

    return result > 0;
}
