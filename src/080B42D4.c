#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x153E];
    s16 value;
} State080B42D4;

/* 0x080B42D4..0x080B42E4: 16 bytes, including alignment and the offset literal. */
s16 func_080B42D4(State080B42D4 *state)
{
    return state->value;
}
