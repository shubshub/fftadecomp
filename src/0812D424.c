#include "ffta.h"

/* Target: complete [0x0812D424, 0x0812D472), 78 bytes. */
extern s32 func_080C7EA4(const void *, u32);
extern s32 func_080CA7A4(u16, u8);

u32 func_0812D424(const void *object, const u16 *values, s32 count)
{
    s32 slot;

    for (slot = 0; slot < 5; slot++) {
        s32 entry = func_080C7EA4(object, (u8)(slot + 0x1d));

        if (entry != 0) {
            s32 value = func_080CA7A4(entry, 3);
            s32 index;

            for (index = 0; index < count; index++) {
                if (value == values[index])
                    return 1;
            }
        }
    }
    return 0;
}
