#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54D4];
    u8 unknown_54d4;
} State080C19A8;

extern State080C19A8 data_020101F8;

/* 0x080C19A8..0x080C19BC: 20 complete bytes, including both literal words. */
u8 func_080C19A8(void)
{
    State080C19A8 *state = &data_020101F8;

    return state->unknown_54d4 >> 4;
}
