#include "ffta.h"

/* 0x081443B0..0x081443FC: 76 bytes, 38 instructions. */
s32 func_081443B0(const void *first, const void *second, s32 count)
{
    u8 *left = (u8 *)first;
    u8 *right = (u8 *)second;

    if (count >= sizeof(u32) && !(((u32)left | (u32)right) & 3)) {
        unsigned long *left_words = (unsigned long *)left;
        unsigned long *right_words = (unsigned long *)right;

        while (count >= sizeof(u32)) {
            if (*left_words != *right_words)
                break;
            left_words++;
            right_words++;
            count -= sizeof(u32);
        }
        left = (u8 *)left_words;
        right = (u8 *)right_words;
    }

    while (count-- != 0) {
        s32 difference = *left;
        s32 right_value = *right;

        if (difference != right_value) {
            difference -= right_value;
            return difference;
        }
        left++;
        right++;
    }
    return 0;
}
