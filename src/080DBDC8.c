#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

extern void func_0801C984(s16 x, s16 y, s16 z, s16 *screen_x,
                          s16 *screen_y);

/* 080DBDC8..080DBDEC: 36 bytes, 17 instructions. */
void func_080DBDC8(const PositionState *state, s16 *screen_x, s16 *screen_y)
{
    func_0801C984(state->x, state->y, state->z, screen_x, screen_y);
}
