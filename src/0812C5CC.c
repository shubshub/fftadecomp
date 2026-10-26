#include "ffta.h"

extern u16 func_0812E6A4(u32 subject);
extern s32 func_080CA7A4(u16 entry, u8 selector);

/* Target: [0x0812C5CC, 0x0812C60E), 66 bytes, 31 instructions. */
u32 func_0812C5CC(u32 subject, u16 entry, u8 allow_seven)
{
    u16 kind = func_0812E6A4(subject);

    if (kind == 7 && allow_seven == 0)
        kind = 0;
    if (kind != 7 && kind != 5) {
        s32 value;

        if (kind != 6)
            return 0;
        value = func_080CA7A4(entry, 3);
        if (value != 13 && value != 14)
            return 0;
    }
    return 1;
}
