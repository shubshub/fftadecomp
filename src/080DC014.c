#include "ffta.h"

/* 0x080DC014..0x080DC058: 68 bytes.
 * 70b584b06d460a3503ab0821445e0a22815e0c26825f00950193201c02ab40f771fc02a80088
 * 7838000400142988603909040914fcf76efd0006000e04b070bc02bc0847
 */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                         s16 *screen_y, s16 *depth);
extern int func_080D8B28(s16 x, s16 y);

/* 0x080DC014..0x080DC058: 68 complete bytes. */
u8 func_080DC014(const PositionState *state)
{
    s16 projected[3];
    s16 *screen_y = &projected[1];
    s16 *depth = &projected[2];

    func_0801C918(state->x, state->y, state->z, &projected[0], screen_y, depth);
    return func_080D8B28((s16)(projected[0] - 120), (s16)(*screen_y - 96));
}
