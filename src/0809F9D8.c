#include "ffta.h"

typedef struct {
    void *object;
    u8 unknown_04[0x24];
    u32 flags;
} ObjectState;

u8 func_080CDADC(const void *object);
u8 func_080CD8E4(const void *object);
u8 func_080CD974(const void *object);

s32 func_0809F9D8(const ObjectState *state)
{
    s32 result;

    if (func_080CDADC(state->object) ||
        (!(state->flags & 1) && !func_080CD8E4(state->object) &&
         !func_080CD974(state->object) && state->flags == 0))
        result = 0;
    else
        result = 1;
    return result;
}
