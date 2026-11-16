#include "ffta.h"

extern u32 data_03002BB8;
extern u32 data_03002BB0;

/* Target: complete [0x080051C4, 0x08005318), 340 bytes, 153 instructions. */
s32 func_080051C4(const u8 *source, const u8 *dictionary)
{
    u16 completed = 0;
    u8 mode = *dictionary++;
    u8 bits = *dictionary++;
    /* Zeroed at 0x080051E6 (movs r2, #0) although mode 0, the only reader,
     * always takes the mode <= 2 branch that loads it. */
    u16 length = 0;
    u16 mask;
    u16 expected;
    u16 count;
    u16 offset;

    if (mode <= 2) {
        length = (dictionary[0] << 8) | dictionary[1];
        dictionary += 2;
    }
    mask = 0xFFFF;
    mask >>= bits + 1;
    if (mode == 0) {
        expected = length;
    } else if (mode == 3) {
        expected = (source[0] << 8) | source[1];
        source += 2;
    } else {
        return 0;
    }

    while (completed != expected) {
        if (*source & 0x80) {
            count = (*source++ & 0x7F) + 1;
            completed += count;
            while (count-- != 0) {
                u8 value = *source++;
                ((u8 *)data_03002BB8)[data_03002BB0++] = value;
            }
        } else {
            count = *source << 1;
            count >>= 8 - bits;
            count += 3;
            offset = (source[0] << 8) | source[1];
            offset &= mask;
            completed += count;
            while (count-- != 0) {
                u8 value = dictionary[offset++];
                ((u8 *)data_03002BB8)[data_03002BB0++] = value;
            }
            source += 2;
        }
        if (completed > expected)
            return 0;
    }
    return 1;
}
