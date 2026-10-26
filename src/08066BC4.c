#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 frame;
    u8 unknown_0a[4];
    s16 timer;
} Animation08066BC4;

typedef struct {
    u8 unknown_00[9];
    u8 active;
    u8 unknown_0a[2];
    Animation08066BC4 first;
    Animation08066BC4 second;
} State08066BC4;

typedef struct {
    u8 unknown_00[0x12];
    u8 mode;
} Global08066BC4;

extern Global08066BC4 g_state_020020D0;
extern void func_08017FE8(Animation08066BC4 *);

/* Complete [0x08066BC4, 0x08066C28): 100 bytes, 45 instructions. */
void func_08066BC4(State08066BC4 *state)
{
    if (state->active && g_state_020020D0.mode != 3) {
        if (++state->first.timer > 5) {
            state->first.timer = 0;
            if (++state->first.frame > 2)
                state->first.frame = 0;
            if (--state->second.frame <= -3)
                state->second.frame = 0;
        }
        func_08017FE8(&state->first);
        func_08017FE8(&state->second);
    }
}
