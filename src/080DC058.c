#include "ffta.h"

/* 0x080DC058..0x080DC0A4: 76 bytes.
 * 70b584b00906090e01f028fa6d460a3503ab0821445e0a22815e0c26825f00950193201c02ab
 * 40f74bfc02a800887838000400142988603909040914fcf748fd0006000e04b070bc02bc0847
 */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                         s16 *screen_y, s16 *depth);
typedef struct Group Group;
extern u32 func_080DD4B4(Group *group, u8 index);
extern int func_080D8B28(s16 x, s16 y);

u8 func_080DC058(Group *group, u8 index)
{
    const PositionState *state;
    s16 projected[3];
    s16 *screen_y;
    s16 *depth;

    state = (const PositionState *)func_080DD4B4(group, index);
    screen_y = &projected[1];
    depth = &projected[2];
    func_0801C918(state->x, state->y, state->z, &projected[0], screen_y, depth);
    return func_080D8B28((s16)(projected[0] - 120), (s16)(*screen_y - 96));
}
