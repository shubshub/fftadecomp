#include "ffta.h"

/* 0x08134A10..0x08134AFC: 236 bytes. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xAC];
    u16 counter;
    u8 unknown_D8[0x18];
    u8 result;
    u8 unknown_F1[0x11];
    u8 counterA;
    u8 counterB;
    u8 id;
} Unit;

typedef struct {
    u8 unknown_00[0x3C34];
    u8 selectors[256][2];
} GameState;

extern GameState g_state_02000000;
extern u8 func_080C832C(Unit *unit);
extern u8 func_080C82B8(Unit *unit);
extern void func_0802DC60(u8 id, u8 selector, u32 active);
extern u8 func_080C95A8(u32 category);
extern u8 func_080D2F0C(Unit *unit);

u8 func_08134A10(Unit *unit, u32 unknown_1, u32 unknown_2,
                 u32 unknown_3, u32 unknown_4, u32 unknown_5,
                 u8 mode, u32 unknown_7, u8 selector)
{
    u32 index;

    if (!selector)
        return 0;
    index = selector - 1;
    if (func_080C832C(unit) && mode != 3)
        mode = 2;
    if (mode == 1 || !func_080C82B8(unit)) {
        func_0802DC60(unit->id, g_state_02000000.selectors[index][0], mode != 1);
    }
    unit->counter = 0;
    if (func_080C82B8(unit))
        mode = 1;
    if (mode != 1) {
        if (unit->counterA <= 8 && func_080C95A8(13) != 1)
            ++unit->counterA;
        unit->flags |= 0x68;
        unit->result = func_080D2F0C(unit);
    } else {
        if (unit->counterB <= 8 && func_080C95A8(13) != 1)
            ++unit->counterB;
        unit->flags |= 0x40;
    }
    return mode;
}
