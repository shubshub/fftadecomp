#include "ffta.h"

/* 0x080CDC74..0x080CDC8C: 24 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xED];
    u8 flags;
} ObjectState;

u32 func_080CDC74(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 2;
    u32 flags = *flag_byte;

    if (!(flags & mask)) {
        return 0;
    }
    return 1;
}
