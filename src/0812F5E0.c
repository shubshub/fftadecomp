#include "ffta.h"

typedef struct Unit Unit;

extern u8 func_080CD95C(const Unit *unit);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern s32 func_080CA7A4(u16 entry, u8 field);
extern s32 func_08130820(const Unit *unit);
extern s32 func_080C7EA4(const void *unit, u32 selector);

/* [0x0812F5E0, 0x0812F690), 176 bytes. */
s32 func_0812F5E0(const Unit *unit, u16 entry, u32 attribute)
{
    u16 field = attribute;
    u16 selected[2];
    s32 count, total, i, j;

    if (func_080CD95C(unit))
        return 0;
    total = 0;
    count = func_0812F0D8(unit, selected);
    if (count <= 0)
        count = 0;
    if (field != 10) {
        count = 0;
    } else if (entry) {
        total = func_080CA7A4(entry, 10);
    } else {
        total = func_08130820(unit);
    }
    for (i = 0; i < 5; i++) {
        u16 item = func_080C7EA4(unit, (u8)(i + 29));
        if (!item)
            continue;
        for (j = 0; j < count; j++)
            if (selected[j] == item)
                break;
        if (j < count)
            continue;
        total += func_080CA7A4(item, field);
    }
    return total;
}
