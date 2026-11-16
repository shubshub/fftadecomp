#include "ffta.h"

/* Complete [0x081302F8, 0x0813034A): 82 bytes, 38 instructions.
 * Target: f0b5071c05980906090e1206120e1b061d0e0006060e381cfd300078052814d008
 * 1c111cecf67cfc041c2406240e281c311cecf675fc0006000e241a381c211c00f008f8
 * 0004001400e00020f0bc02bc0847
 *
 * Unless the unit's byte at 0xFD is 5, returns func_0813034C(unit, height of
 * (x, y) - height of (other_x, other_y)), heights from func_0801CC18.
 */
typedef struct {
    u8 unknown_00[0xFD];
    u8 movement;
} Unit;

extern u8 func_0801CC18(u8 column, u8 row);
extern s16 func_0813034C(void *unit, s16 limit);

/* The coordinates are s8: the only caller, func_080A23B8, sign-extends all
 * four arguments before both calls (0x080A2A14..0x080A2A2A and 0x080A3502..
 * 0x080A351E), as agbcc does for s8 parameters.  Used only as u8, they are
 * narrowed with lsrs at entry here. */
s16 func_081302F8(Unit *unit, s8 x, s8 y, s8 other_x, s8 other_y)
{
    u8 height;

    if (unit->movement == 5)
        return 0;
    height = func_0801CC18(x, y);
    return func_0813034C(unit, height - func_0801CC18(other_x, other_y));
}
