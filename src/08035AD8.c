#include "ffta.h"

extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08142AB0(u32 value, u32 divisor);
extern u32 func_08142B28(u32 value, u32 divisor);

/* Write the number right-aligned and pad free columns with the zero glyph. */
void func_08035AD8(u16 *dst, u16 count, u32 value, u16 base)
{
    u16 clear;
    u16 *fill = &clear;
    u16 remaining;

    *fill = 0;
    func_0814186C(fill, dst, 0x01000000 | count);
    dst += count;
    dst--;

    for (remaining = count; remaining != 0;) {
        *dst-- = func_08142B28(value, 10) + (u16)(base + 0x1e);
        remaining--;
        value = func_08142AB0(value, 10);
        if (value == 0)
            break;
    }
    if (remaining != 0) {
        *dst-- = base + 0x1e;
        remaining--;
        while (remaining != 0) {
            *dst-- = base + 0x1e;
            remaining--;
        }
    }
}
