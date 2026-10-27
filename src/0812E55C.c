#include "ffta.h"

extern u8 func_080CD95C(const void *object);
extern s32 func_0812E4F4(const void *object, u16 *entries);
extern s32 func_080CA7A4(u16 entry, u8 attribute);

/* Complete [0x0812E55C, 0x0812E5B4): 88 bytes, 40 instructions. */
s32 func_0812E55C(const void *object, u16 *entries)
{
    s32 count;

    entries[0] = 0;
    entries[1] = 0;
    if (func_080CD95C(object) != 0)
        return 0;
    count = func_0812E4F4(object, entries);
    if (count <= 1)
        return count;
    {
        s8 first = func_080CA7A4(entries[0], 10);
        s8 second = func_080CA7A4(entries[1], 10);

        if (first < second) {
            u16 temporary = entries[0];
            entries[0] = entries[1];
            entries[1] = temporary;
        }
    }
    return count;
}
