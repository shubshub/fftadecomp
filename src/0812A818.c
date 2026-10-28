#include "ffta.h"

extern u16 func_0812B5D4(const u8 *text);

/* Target: [0x0812A818, 0x0812A876), 94 bytes, 46 instructions. */
u32 func_0812A818(const u8 *text, const u8 *prefix)
{
    u16 length = func_0812B5D4(prefix);
    u16 i;

    for (i = 0; i < length; i++) {
        const u8 *character = text + i * 2;
        const u8 *prefix_character = prefix + i * 2;

        if (character[0] != prefix_character[0] ||
            character[1] != prefix_character[1])
            return 0;
    }
    for (; i < 9; i++) {
        const u8 *character = text + i * 2;

        if (character[0] != 0x40 || character[1] != 0x73)
            return 0;
    }
    return 1;
}
