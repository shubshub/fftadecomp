#include "ffta.h"

/* 0812DAB8 .. 0812DAEA: 50 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 progress;
} PathState;

extern s32 func_0812C8DC(PathState *, void *, s32, s32);

s32 func_0812DAB8(PathState *state, void *argument)
{
    if (state->count >= (u16)(state->progress / 10u) || state->count > 9)
        return 0;
    return func_0812C8DC(state, argument, 2, 0);
}
