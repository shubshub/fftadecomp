#include "ffta.h"

/* 0x080D61E4..0x080D620A: 38 bytes. */
typedef struct {
    u8 unknown_00[0x0E];
    u8 flags;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

void func_080D61E4(int index, u8 enabled)
{
    ObjectState *state = func_08005BFC(index);

    if (enabled)
        state->flags |= 8;
    else
        state->flags &= ~8;
}
