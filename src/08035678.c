#include "ffta.h"

/* 0x08035678..0x080356A0: 40 bytes / 20 instructions. */
void func_08035678(u16 value, u16 *destination, u32 count, u16 step)
{
    u32 index;

    for (index = 0; index < count; ++index) {
        *destination++ = value;
        value += step;
    }
}
