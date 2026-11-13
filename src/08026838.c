#include "ffta.h"

// 0x08026838..0x080268DA: 162 bytes, 81 instructions.

typedef struct {
    u8 unknown_000[0xE6];
    u8 unknown_0E6;
    u8 unknown_0E7[0x104 - 0xE7];
    u8 unknown_104;
} Unit08026838;

typedef struct {
    Unit08026838 *unit;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
} Object08026838;

extern void *func_08096D7C(void);
extern Object08026838 *func_08099560(void *context, Unit08026838 *unit);
extern u32 func_08099D08(void *context, Object08026838 **list);
extern u8 func_08025F70(Unit08026838 *unit);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_080CDBCC(Unit08026838 *unit);

u8 func_08026838(Unit08026838 *unit)
{
    Object08026838 *objects[13];
    s32 x, y;
    s32 count, i;

    objects[0] = func_08099560(func_08096D7C(), unit);
    x = objects[0]->x >> 5;
    y = objects[0]->y >> 5;
    if (func_08025F70(unit) || func_0801CD08(x, y) == 2)
        return 1;

    /* The ROM stores the func_08099560 result into the first buffer slot
       before the query overwrites it. */
    count = func_08099D08(func_08096D7C(), objects);
    for (i = 0; i < count; i++) {
        Unit08026838 *other = objects[i]->unit;

        if (unit->unknown_104 != other->unknown_104 && func_080CDBCC(other)
            && other->unknown_0E6 == unit->unknown_104)
            return 1;
    }
    return 0;
}
