#include "ffta.h"

extern s32 func_080C7EA4(const void *object, u32 selector);
extern s32 func_080CA7A4(u16 entry, u8 selector);

s8 func_081329EC(const void *object)
{
    s32 slot;

    for (slot = 0; slot < 5; slot++)
    {
        u16 entry = func_080C7EA4(object, (u8)(slot + 0x1D));
        if (entry != 0)
        {
            u8 type = func_080CA7A4(entry, 3);
            if (type == 0x1A || type == 0x18 || type == 0x19)
                return slot;
        }
    }
    return -1;
}
