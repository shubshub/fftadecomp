#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} ObjectState;

u8 func_080CD9EC(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 0x40;
    u32 flags = *flag_byte;

    if (!(flags & mask))
        return 0;
    return 1;
}
