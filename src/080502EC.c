#include "ffta.h"

struct State080502EC {
    u8 unknown_000[0x560];
    u8 row;
    u8 unknown_561;
    u8 column;
    u8 subrow;
};

struct Owner080502EC {
    struct State080502EC *state;
};

/* Complete target: [0x080502EC, 0x0805033C), 80 bytes. */
u32 func_080502EC(struct Owner080502EC *owner)
{
    u32 row = owner->state->row;
    u16 result = row * 18 + 1;

    if (row == 16 && owner->state->subrow == 2)
        owner->state->subrow = 1;

    return result + owner->state->subrow * 6 + owner->state->column;
}
