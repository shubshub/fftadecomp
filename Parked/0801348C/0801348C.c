#include "ffta.h"

/* 0x0801348C..0x08013526: 154 bytes. */
extern s16 func_0801344C(u16 *, s16);

s16 func_0801348C(u16 *buffer, s16 index, u8 offset)
{
    s16 result = func_0801344C(buffer, index);

    if (offset != 0) {
        u16 *entry = buffer;
        u32 increment = offset & 0xF;
        int remaining = 63;

        increment |= (increment << 4) | (increment << 8) | (increment << 12);
        do {
            if (*entry != 0) {
                u16 value = *entry;

                if (value & 0x000F)
                    value += increment & 0x000F;
                if (value & 0x00F0)
                    value += increment & 0x00F0;
                if (value & 0x0F00)
                    value += increment & 0x0F00;
                if (value & 0xF000)
                    value += increment & 0xF000;
                *entry = value;
            }
            --remaining;
            ++entry;
        } while (remaining >= 0);
    }
    return result;
}
