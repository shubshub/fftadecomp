#include "ffta.h"

typedef struct {
    u8 unknown_00[0xEC];
    u8 flags;
} FlagObject;

void func_080CE21C(void *object, u8 enabled)
{
    FlagObject *state = object;
    u8 mask = 0x20;

    state->flags &= ~mask;
    if (enabled)
        state->flags |= mask;
}
