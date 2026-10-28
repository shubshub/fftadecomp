#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 unknown_0C;
    u16 height;
    u8 flags;
    u8 unknown_11;
    u8 depth_offset;
} DisplayState;

typedef struct {
    u8 unknown_00[0xB0];
    s16 depth;
} DrawingState;

extern const u8 data_0851BA5A[];
extern const u8 data_0851BA52[];
extern DrawingState g_state_020020D0;
extern void func_08001DAC(const void *source, s32 x, s32 y, s32 depth,
                         u8 count, u32 extra);
extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                         u8 first_flag, u8 second_flag, u8 third_flag,
                         u8 fourth_flag, u32 value, u8 count, u32 extra);

/* Complete [0x08017E80, 0x08017F04): 132 bytes, 58 instructions. */
void func_08017E80(void *object)
{
    DisplayState *state = object;
    u8 depth_mode = state->flags & 4;

    if (depth_mode) {
        func_08001DAC(data_0851BA5A, state->x + 15,
                     state->y + state->height + 1,
                     g_state_020020D0.depth + state->depth_offset, 0, 0);
    } else {
        s32 offset = (state->flags & 8) ? 24 : 0;
        func_08001CF0(data_0851BA52, state->x + offset,
                     state->y + state->height, 0, 0, 0,
                     (state->flags >> 3) & 1, 0, 0, 0, 0);
    }
}
