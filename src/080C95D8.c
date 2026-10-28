#include "ffta.h"

/* 0x080C95D8..0x080C960A: 50 bytes, including the literal pool. */
typedef struct {
    u8 unknown_00[0x1F70];
    u8 bits[8192];
} BitState;

u8 func_080C95D8(u16 index, const BitState *state)
{
    const u8 *byte = &state->bits[index >> 3];
    u8 mask = 1 << (index & 7);

    if (*byte & mask)
        return 1;
    return 0;
}
