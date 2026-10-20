#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
} SceneContext;

void func_0809A244(void *context, u32 value)
{
    SceneContext *state = context;

    state->flags &= ~0x10;
    if (value == 0)
        state->flags |= 0x10;
}
