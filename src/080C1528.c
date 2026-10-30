#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54C0];
    u16 value;
} State080C1528;

extern State080C1528 data_020101F8;

/* 080C1528..080C153C: 02 48 03 49 40 18 00 88 70 47 00 00 F8 01 01 02 C0 54 00 00. */
u16 func_080C1528(void)
{
    State080C1528 *state = &data_020101F8;

    return state->value;
}
