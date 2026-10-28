#include "ffta.h"

/* 0x080CA394..0x080CA3EC: 88 bytes. */
typedef struct {
    u8 unknown_00[0x2A];
    u16 equipment[5];
    u8 unknown_34[9];
    u8 status;
} Unit;

extern s8 func_080C92F0(Unit *unit, u32 field);
extern s32 func_080CA7A4(u16 id, u32 field);

s8 func_080CA394(Unit *unit)
{
    s8 value = func_080C92F0(unit, 30);
    s32 total;
    s32 i;

    if (unit->status == 1)
        value++;
    total = 0;
    for (i = 0; i < 5; i++) {
        if (unit->equipment[i] != 0)
            total += func_080CA7A4(unit->equipment[i], 16);
    }
    value += total;
    if (value < 0)
        value = 0;
    return value;
}
