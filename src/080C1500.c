#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54BA];
    u8 unknown_54ba;
} State080C1500;

extern State080C1500 data_020101F8;

/* 0x080C1500..0x080C1514: 20 complete bytes, including alignment and literals. */
u8 func_080C1500(void)
{
    State080C1500 *state = &data_020101F8;

    return state->unknown_54ba;
}
