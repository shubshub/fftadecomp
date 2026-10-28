#include "ffta.h"

typedef struct {
    u8 unknown_00[0xED];
    u8 flags;
} ObjectState;

u8 func_080CDCBC(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 0x10;
    u32 flags = *flag_byte;

    if (!(flags & mask))
        return 0;
    return 1;
}
