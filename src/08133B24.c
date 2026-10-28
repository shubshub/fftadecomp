#include "ffta.h"

/* 0x08133B24..0x08133B3C: 24 bytes, 9 instructions. */
extern u8 data_08527E1C[];
extern u8 func_08131DA4(u8 *flags, s32 index, u8 second);

u8 func_08133B24(const u8 *flags, s32 index, u8 second)
{
    return func_08131DA4(data_08527E1C, index, second);
}
