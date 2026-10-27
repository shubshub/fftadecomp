#include "ffta.h"

struct TransferState
{
    u8 unknown_000[2];
    u8 mode;
    u8 unknown_003[0x121];
    u16 status;
    u8 unknown_126[6];
    u16 completed;
    u16 unknown_12E;
    u16 groups;
    u16 unknown_132;
    u16 position;
    u16 unknown_136;
    u16 length;
    u8 unknown_13A[10];
    const void *source;
    void *destination;
};

extern struct TransferState data_030028A0;

/* Target [0x08003D20, 0x08003D9A): 122 bytes, 58 instructions. */
u32 func_08003D20(const void *source, void *destination, u16 length)
{
    struct TransferState *state = &data_030028A0;
    u8 *phase = (u8 *)&state->status;

    if (state->status != 0x101 || state->mode != 3)
        return 0;

    *phase = 2;
    state->source = source;
    state->destination = destination;
    state->groups = (length + 5) / 6;
    state->length = length;
    state->position = 0;
    state->completed = 0;
    *phase = 5;
    return 1;
}
