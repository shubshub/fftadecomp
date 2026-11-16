#include "ffta.h"

/* Complete [0x081302F8, 0x0813034A): 82 bytes, 38 instructions.
 * Target: f0b5071c05980906090e1206120e1b061d0e0006060e381cfd300078052814d008
 * 1c111cecf67cfc041c2406240e281c311cecf675fc0006000e241a381c211c00f008f8
 * 0004001400e00020f0bc02bc0847
 *
 * Parked: byte-identical only because height_difference takes its
 * coordinates as s16.  With u8 - the type of this function's coordinate
 * parameters and of func_0801CC18's - and in every form without the helper
 * it is 80 bytes; s16, u16, s32, u32 and int all match.  The ROM has no
 * such helper.  See README.md.
 */
typedef struct {
    u8 unknown_00[0xFD];
    u8 movement;
} UnitInfo;

extern u8 func_0801CC18(u8 column, u8 row);
extern s16 func_0813034C(void *unit, s16 limit);

static inline s32 height_difference(s16 x, s16 y, s16 other_x, s16 other_y)
{
    u8 first = func_0801CC18(x, y);
    u8 second = func_0801CC18(other_x, other_y);
    return first - second;
}

s16 func_081302F8(UnitInfo *unit, u8 x, u8 y, u8 other_x, u8 other_y)
{
    if (unit->movement == 5)
        return 0;
    return func_0813034C(unit, height_difference(x, y, other_x, other_y));
}
