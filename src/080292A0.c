#include "ffta.h"

typedef union {
    struct {
        s16 x;
        s16 y;
    } coordinates;
    u32 packed;
} Position080292A0;

typedef struct {
    Position080292A0 current;
    Position080292A0 target;
} Movement080292A0;

typedef struct {
    u8 unknown_00[0x88];
    Movement080292A0 movement;
} State080292A0;

/* Complete [0x080292A0, 0x080292DE): 62 bytes, 31 instructions. */
u8 func_080292A0(State080292A0 *state)
{
    Movement080292A0 *movement = &state->movement;

    if (movement->target.coordinates.x > movement->current.coordinates.x)
        movement->current.coordinates.x += 2;
    if (movement->target.coordinates.y > movement->current.coordinates.y)
        movement->current.coordinates.y += 4;
    if (movement->target.packed == movement->current.packed)
        return 1;
    return 0;
}
