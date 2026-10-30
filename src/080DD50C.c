#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 flags;
    u8 unknown_0e[0x12];
    s16 value;
} State080DD50C;

/* Complete target: [0x080DD50C, 0x080DD52C), 32 bytes. */
s32 func_080DD50C(const State080DD50C *state)
{
    return (state->flags & 2) ? state->value : 0x7FFF;
}
