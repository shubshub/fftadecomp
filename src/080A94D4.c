#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 priority;
    s16 x;
    s16 y;
    u8 unknown_08[8];
    u8 flags;
} DrawState;

typedef struct {
    s8 x;
    u8 unknown_01[3];
    s8 y;
} BytePosition;

extern DrawState data_0200FFC8;
extern BytePosition data_0200F3B8;
extern const u8 data_0839454C[];
extern void func_080A901C(DrawState *state, s32 x, s32 y);
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32,
                          u32, u32, u32, u32, u32);

/* 0x080A94D4..0x080A9528: 84 bytes, including literal pools. */
void func_080A94D4(void)
{
    DrawState *state = &data_0200FFC8;

    func_080A901C(state, data_0200F3B8.x, data_0200F3B8.y);
    if (state->flags & 1) {
        u32 priority = state->priority;

        func_08001CF0(data_0839454C, state->x, state->y,
                       0, 0, 0, 0, 0, 0, priority, 0);
    }
}
