#include "ffta.h"

/* 0x08133ADC..0x08133B24: 72 bytes, 35 instructions. */
extern u8 func_081339CC(const void *subject, s32 index, u32 option);

static inline u8 bit_is_set(const u8 *bits, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;
    s32 value = bits[byte_index];

    if ((value >> bit_index) & 1)
        return 1;
    else
        return 0;
}

u8 func_08133ADC(const u8 *bits, const void *subject)
{
    s32 index;

    for (index = 0; index < 44; index++) {
        if (bit_is_set(bits, index) &&
            !func_081339CC(subject, index, 0))
            return 0;
    }
    return 1;
}
