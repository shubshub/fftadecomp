#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54D5];
    u8 value;
} State080C19F0;

extern State080C19F0 data_020101F8;

/* 080C19F0..080C1A04: 02 48 03 49 40 18 00 78 70 47 00 00 F8 01 01 02 D5 54 00 00. */
u8 func_080C19F0(void)
{
    State080C19F0 *state = &data_020101F8;

    return state->value;
}
