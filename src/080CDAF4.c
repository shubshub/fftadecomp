#include "ffta.h"

/* 0x080CDAF4..0x080CDB0C: 24 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xEB];
    u8 flags;
} ObjectState;

u32 func_080CDAF4(const ObjectState *state)
{
    const u8 *flag_byte = &state->flags;
    u32 mask = 1;
    u32 flags = *flag_byte;

    if (!(flags & mask)) {
        return 0;
    }
    return 1;
}
