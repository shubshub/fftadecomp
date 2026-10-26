#include "ffta.h"

/* 0x080CBA14..0x080CBA3C: 40 bytes, 18 instructions, including a pool. */
extern const u8 data_083B8F50[];

u32 func_080CBA14(u8 index)
{
    if (index > 0x52) {
        index = 0x2D;
    } else if (index > 0x2B) {
        index = 0x2C;
    }
    return data_083B8F50[index * 4 - 4] >> 4;
}
