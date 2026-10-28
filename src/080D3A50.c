#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State;

extern void *data_020159C0;
extern State *func_08005BFC(void *object);

void func_080D3A50(u8 disabled)
{
    State *state = func_08005BFC(data_020159C0);

    if (disabled)
        state->flags &= ~4;
    else
        state->flags |= 4;
}
