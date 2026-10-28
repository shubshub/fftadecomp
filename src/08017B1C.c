#include "ffta.h"

/* Target: complete [0x08017B1C, 0x08017B44), 40 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 field_12;
} State08017B1C;

extern void func_0801799C(State08017B1C *state, s8 row, u8 style, u8 value);

void func_08017B1C(State08017B1C *state, u8 row, u8 style)
{
    if (!(state->flags & 1))
        func_0801799C(state, (s8)row, style, state->field_12);
}
