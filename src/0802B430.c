#include "ffta.h"

/* 0x0802B430..0x0802B45E: 46 bytes. */
typedef struct {
    u8 unknown_00[8];
    u16 second;
    u8 unknown_0A[0xA];
    u16 first;
    u8 unknown_16[2];
    u16 third;
} ValueState;

u16 func_0802B430(const ValueState *state, u8 index)
{
    switch (index) {
    case 0:
        return state->first;
    case 1:
        return state->second;
    case 2:
        return state->third;
    default:
        return 0;
    }
}
