#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 value;
} State080A9478;

extern State080A9478 data_0200FFC8;

/* 080A9478..080A9484: 01 49 C8 70 70 47 00 00 C8 FF 00 02. */
void func_080A9478(u8 value)
{
    State080A9478 *state = &data_0200FFC8;

    state->value = value;
}
