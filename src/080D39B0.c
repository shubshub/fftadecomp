#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State;

extern void *data_020159C0;
extern State *func_08005BFC(void *object);

u8 func_080D39B0(void)
{
    State *state = func_08005BFC(data_020159C0);

    if (state->flags & 2)
        return 1;
    return 0;
}
