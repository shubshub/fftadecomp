#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 flags;
    u8 unknown_0E[0x14];
    s16 value;
} State080DD52C;

/* Target bytes [080DD52C, 080DD54C):
 * 00 B5 02 1C 91 89 04 20 08 40 04 49 00 28 01 D0
 * 22 20 11 5E 08 1C 02 BC 08 47 00 00 FF 7F 00 00.
 */
s32 func_080DD52C(const State080DD52C *state)
{
    return state->flags & 4 ? state->value : 0x7FFF;
}
