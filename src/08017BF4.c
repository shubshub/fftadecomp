#include "ffta.h"

/* 0x08017BF4..0x08017C28: 52 bytes. */
typedef struct {
    u8 unknown_00[0x13];
    u8 field_13;
    u8 unknown_14;
    u8 field_15;
} Owner08017BF4;

typedef struct {
    u32 unknown_00;
    Owner08017BF4 *owner;
    u8 unknown_08[8];
    u8 flags;
} State08017BF4;

u16 func_08017BF4(const State08017BF4 *state)
{
    u8 extra;

    if (state->owner == 0)
        return 0;
    if (state->flags & 8)
        extra = state->owner->field_15 + 1;
    else
        extra = 0;
    return (state->owner->field_13 + extra - 3) * 8;
}
