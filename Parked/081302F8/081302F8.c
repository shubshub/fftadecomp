#include "ffta.h"

/* 0x081302F8..0x0813034A: 82 bytes. */
typedef struct {
    u8 unknown_00[0xFD];
    u8 mode;
} UnitInfo;

extern u8 func_0801CC18(u8 x, u8 y);
extern s16 func_0813034C(UnitInfo *unit, s16 limit);

static inline s32 height_difference(u8 x, u8 y, u8 other_x, u8 other_y)
{
    u8 first = func_0801CC18(x, y);
    u8 second = func_0801CC18(other_x, other_y);
    return first - second;
}

s16 func_081302F8(UnitInfo *unit, u8 x, u8 y, u8 other_x, u8 other_y)
{
    if (unit->mode == 5)
        return 0;
    return func_0813034C(unit, height_difference(x, y, other_x, other_y));
}
