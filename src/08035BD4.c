#include "ffta.h"

// Complete 08035BD4..08035C48: 116 bytes, 53 instructions.
// Clears an eight-halfword buffer, then writes `value` right-aligned in
// decimal as tile codes (base + 0xA9 + digit) ending at dst[count - 1],
// padding the remaining digits with the tile base + 0xB3.

extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);

void func_08035BD4(u16 *dst, u16 count, u32 value, u16 base)
{
    u16 clear;
    u16 *fill = &clear;
    u16 i;

    *fill = 0;
    func_0814186C(fill, dst, 0x01000008);
    dst += count;
    dst--;
    for (i = count; i != 0;) {
        *dst-- = func_08142B28(value, 10) + (u16)(base + 0xA9);
        i--;
        value = func_08142AB0(value, 10);
        if (value == 0)
            break;
    }
    for (; i != 0; i--)
        *dst-- = base + 0xB3;
}
