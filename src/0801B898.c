#include "ffta.h"

/* 0x0801B898 .. 0x0801B938: 160 bytes. */
typedef struct {
    s16 position;
    u8 unknown_02[38];
    u32 remaining;
} Interpolation0801B898;

typedef struct {
    u8 active;
    u8 unknown_01;
    s16 target_x;
    s16 target_y;
    u16 unknown_06;
    Interpolation0801B898 horizontal;
    Interpolation0801B898 vertical;
    u8 minimum_speed;
    u8 unknown_61;
    u8 speed_step;
    u8 speed;
    u32 deceleration_distance;
    u8 decelerating;
} Motion0801B898;

typedef struct {
    u8 unknown_00[0x24];
    s16 x;
    s16 y;
} Position0801B898;

extern Motion0801B898 data_02007F74;
extern Position0801B898 g_state_02007F40;
extern void func_0800777C(void *state, u16 count);
extern void func_0801E5E0(u32 x, s16 y);

void func_0801B898(void)
{
    Motion0801B898 *state = &data_02007F74;

    func_0800777C(&state->horizontal, state->speed);
    func_0800777C(&state->vertical, state->speed);
    func_0801E5E0(state->horizontal.position, state->vertical.position);

    if (!state->decelerating) {
        if (state->horizontal.remaining <= state->deceleration_distance)
            state->decelerating = 1;
    }

    if (!state->decelerating) {
        state->speed += state->speed_step;
    } else {
        state->speed -= state->speed_step;
        if (state->speed < state->minimum_speed)
            state->speed = state->minimum_speed;
    }

    if (state->target_x == g_state_02007F40.x &&
        state->target_y == g_state_02007F40.y)
        state->active = 0;
}
