#include "ffta.h"

/* 0x08133B3C..0x08133B84: 72 bytes. */
extern u8 func_08133B24(const u8 *, int, int);

static inline u8 is_bit_set(const u8 *bits, int index)
{
    int byte_index = index >> 3;
    int bit_index = index & 7;

    if ((bits[byte_index] >> bit_index) & 1)
        return 1;
    return 0;
}

u8 func_08133B3C(const u8 *required, const u8 *available)
{
    int i;

    for (i = 0; i < 44; ++i) {
        if (is_bit_set(required, i)) {
            if (!func_08133B24(available, i, 0))
                return 0;
        }
    }
    return 1;
}
