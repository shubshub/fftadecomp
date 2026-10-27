#include "ffta.h"

typedef struct {
    u16 unknown_00[10];
    u16 flags;
} State080112A4;

void func_080112A4(State080112A4 *state, u8 enabled)
{
    if (enabled) {
        state->flags |= 0x1000;
    } else {
        state->flags &= ~0x1000;
    }
}
