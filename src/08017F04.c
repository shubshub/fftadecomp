#include "ffta.h"

typedef struct {
    u32 unknown_00;
    const void *subject;
    u16 x;
    u16 y;
    u16 counter;
    u8 unknown_0E[2];
    u8 flags;
    u8 displacement;
} DisplayState;

typedef struct {
    u8 unknown_00[0xB0];
    s16 depth;
} DrawingState;

extern const u8 data_0851BA62[];
extern DrawingState g_state_020020D0;
extern u8 func_08017B48(const void *subject);
extern void func_08001DAC(const void *source, s32 x, s32 y, s32 depth,
                          u8 count, u32 extra);
extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);

/* 08017F04..08017FA8: 164 bytes, 75 instructions. */
void func_08017F04(DisplayState *state)
{
    if (!(state->flags & 0x40)) {
        state->counter = (state->counter + 1) & 7;
        if (state->counter == 0)
            state->displacement ^= 1;
    }

    if (state->flags & 4) {
        func_08001DAC(data_0851BA62, state->x,
                     state->y - state->displacement,
                     g_state_020020D0.depth, 0, 0);
    }

    if (state->flags & 8) {
        u16 y = (func_08017B48(state->subject) << 3) + 8 + state->y;
        s32 displaced_y = y + state->displacement;

        func_08001CF0(data_0851BA62, state->x, displaced_y,
                     0, 0, 0, 0, 1, g_state_020020D0.depth, 0, 0);
    }
}
