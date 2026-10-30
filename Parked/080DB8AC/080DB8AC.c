#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

extern void func_0801C984(s16 x, s16 y, s16 z, s16 *screen_x,
                          s16 *screen_y);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *first,
                          s16 *second, s16 *third);
extern u8 func_080D8604(const s16 *rectangle, const void *bounds,
                       s32 first, s32 second);
extern u8 func_080D8B28(s16 x, s16 y);

/* 0x080DB8AC..0x080DB942: 150 complete bytes, including one literal word. */
u8 func_080DB8AC(const PositionState *state)
{
    const void *bounds = (const void *)0x083955A0;
    s16 screen[2];
    s16 projected[3];
    s16 rectangle[4];

    func_0801C984(state->x, state->y, state->z, &screen[0], &screen[1]);
    rectangle[0] = screen[0] - 16;
    rectangle[2] = screen[0] + 16;
    rectangle[1] = screen[1] - 32;
    rectangle[3] = screen[1] + 8;
    if (func_080D8604(rectangle, bounds, 0, 0))
        return 0;

    func_0801C918(state->x, state->y, state->z,
                  &projected[0], &projected[1], &projected[2]);
    return func_080D8B28((s16)(projected[0] - 120), (s16)(projected[1] - 96));
}
