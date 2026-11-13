#include "ffta.h"

// Target: complete [0x081022AC, 0x081023E8), 316 bytes, 150 instructions.

typedef struct {
    u8 unknown_00[0x0C];
    s8 facing;
    u8 unknown_0D[3];
    Struct08011040 *object;
    Struct08011040 *followers[4];
    u8 unknown_24[0x1E0];
    s8 step;
    s8 follower_steps[4];
    u8 unknown_209[3];
    u16 x;
    u8 unknown_20E[2];
    u16 z;
} State;

extern const s8 data_0839EFCC[];
extern void func_080107D4(Struct08011040 *, s16, s16, s16);

void func_081022AC(State *state)
{
    s16 x, y, z;
    s8 offset;
    u8 i;

    if (state->step <= 0x2F) {
        offset = data_0839EFCC[state->step];
        if (state->facing > 1)
            offset = -offset;
        func_08011040(state->object, (u16 *)&x, (u16 *)&y, (u16 *)&z);
        x = state->x + offset;
        z = state->z - offset;
        func_080107D4(state->object, x, y, z);
        state->step++;
    }

    for (i = 0; i < 4; i++) {
        if (state->follower_steps[i] < 0) {
            state->follower_steps[i]++;
        } else if (state->follower_steps[i] <= 0x2F) {
            offset = data_0839EFCC[state->follower_steps[i]];
            if (state->facing > 1)
                offset = -offset;
            func_08011040(state->followers[i], (u16 *)&x, (u16 *)&y, (u16 *)&z);
            x = state->x + offset;
            z = state->z - offset;
            func_080107D4(state->followers[i], x, y, z);
            state->follower_steps[i]++;
        }
    }
}
