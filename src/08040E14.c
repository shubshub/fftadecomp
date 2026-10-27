#include "ffta.h"

/* 0x08040E14..0x08040E30: 28 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0x1A];
    u16 frame;
} AnimationState;

extern void func_08040D3C(AnimationState *state);
extern void func_08040DA4(AnimationState *state, u16 frame);

void func_08040E14(s32 index, AnimationState *state)
{
    func_08040D3C(state);
    func_08040DA4(state, state->frame * 2);
}
