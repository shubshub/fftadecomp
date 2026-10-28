#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 flags;
} State;

extern State *func_08005BFC(void *object);

void func_080D3FF8(void *object, u8 enabled)
{
    State *state = func_08005BFC(object);

    if (enabled)
        state->flags |= 0x80;
    else
        state->flags &= ~0x80;
}
