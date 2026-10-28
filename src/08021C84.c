#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 first;
    u16 unknown_14;
    u16 second;
} PairState;

/* 08021C84..08021C8A: 6 bytes, 3 instructions. */
void func_08021C84(PairState *state, u16 first, u16 second)
{
    state->first = first;
    state->second = second;
}
