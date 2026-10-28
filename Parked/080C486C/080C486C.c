#include "ffta.h"

/* Complete [0x080C486C, 0x080C48A4): 56 bytes, 26 instructions. */
s32 func_080C486C(const u8 *state, u32 *output)
{
    if (*(const u16 *)(state + 0x2964) != 0) {
        const u8 *record = state + 0x5C;
        s32 remaining = *(const u16 *)(state + 0x2964);

        do {
            *output++ = *(const u32 *)record;
            record += 0x328;
            --remaining;
        } while (remaining != 0);
    }
    return *(const s16 *)(state + 0x2964);
}
