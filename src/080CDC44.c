#include "ffta.h"

/* 0x080CDC44..0x080CDC5C: 24 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xEC];
    u8 flags;
} ObjectState;

u32 func_080CDC44(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 0x80;
    u32 flags = *flag_byte;

    if (!(flags & mask)) {
        return 0;
    }
    return 1;
}
