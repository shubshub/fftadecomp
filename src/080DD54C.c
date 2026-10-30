#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 flags;
    u8 unknown_0e[0x16];
    s16 value;
} State080DD54C;

/* 0x080DD54C..0x080DD56C:
 * 00 B5 02 1C 91 89 08 20 08 40 04 49 00 28 01 D0
 * 24 20 11 5E 08 1C 02 BC 08 47 00 00 FF 7F 00 00. */
s32 func_080DD54C(const State080DD54C *state)
{
    return (state->flags & 8) ? state->value : 0x7FFF;
}
