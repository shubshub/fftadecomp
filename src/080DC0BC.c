#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

extern u8 func_080DB838(const PositionState *state);
extern u8 func_080DB8AC(const PositionState *state);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                         s16 *screen_y, s16 *depth);
extern int func_080D8B28(s16 x, s16 y);

/* 0x080DC0BC..0x080DC12C: 112 complete bytes. */
u8 func_080DC0BC(const PositionState *state, u8 mode)
{
    s16 projected[3];
    u8 result = 0;

    switch (mode) {
    case 0:
        result = func_080DB838(state);
        break;
    case 1: {
        s16 *screen_y = &projected[1];
        s16 *depth = &projected[2];

        func_0801C918(state->x, state->y, state->z, &projected[0], screen_y, depth);
        result = func_080D8B28((s16)(projected[0] - 120), (s16)(*screen_y - 96));
        break;
    }
    case 2:
        result = func_080DB8AC(state);
        break;
    }
    return result;
}
