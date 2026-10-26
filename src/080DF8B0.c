#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} ObjectState;

extern ObjectState *func_080DD350(void *object);

u8 func_080DF8B0(void *object)
{
    ObjectState *state = func_080DD350(object);

    if (state->flags & 0x20)
        return 1;
    return 0;
}
