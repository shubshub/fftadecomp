#include "ffta.h"

/* 0x080CDA1C..0x080CDA34: 24 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xEA];
    u8 flags;
} ObjectState;

u32 func_080CDA1C(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 1;
    u32 flags = *flag_byte;

    if (!(flags & mask)) {
        return 0;
    }
    return 1;
}
