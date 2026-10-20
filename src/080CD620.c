#include "ffta.h"

s32 func_080C7EA4(const void *object, u32 selector);

void func_080CD620(void *object, u8 index)
{
    if (func_080C7EA4(object, 3) == 4) {
        u8 opposite;
        u8 *values;

        if (index == 0x1A)
            opposite = 0x21;
        else if (index == 0x21)
            opposite = 0x1A;
        else
            return;
        values = (u8 *)object + 0x40;
        values[opposite] = values[index];
    }
}
