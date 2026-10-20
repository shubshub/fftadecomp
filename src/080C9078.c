#include "ffta.h"

s32 func_080C7EA4(const void *object, u32 selector);
u32 func_080C8570(u8 first, u8 second, u8 selector);

u8 func_080C9078(const void *data)
{
    const u8 *object = data;
    s32 first = 2;
    s32 last = 0x73;
    s32 index;

    switch (func_080C7EA4(object, 3)) {
    case 1:
        first = 2;
        last = 0x0C;
        break;
    case 2:
        first = 0x0D;
        last = 0x13;
        break;
    case 3:
        first = 0x14;
        last = 0x1B;
        break;
    case 4:
        first = 0x1C;
        last = 0x23;
        break;
    case 5:
        first = 0x24;
        last = 0x2B;
        break;
    }
    for (index = first; index <= last; index++) {
        u8 value;

        if ((index >= 0x50 && index <= 0x52) || index == 0x55)
            continue;
        value = object[0x36];
        if (value == func_080C8570(index, index, 0x0C))
            return index;
    }
    if (func_080C7EA4(object, 3) == 1) {
        u8 value = object[0x36];

        if (value == func_080C8570(0x4D, 0x4D, 0x0C))
            return 0x4D;
    }
    return 0;
}
