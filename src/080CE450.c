#include "ffta.h"

/* 0x080CE450..0x080CE456: 6 bytes. */
typedef struct {
    u8 unknown_00[0xDF];
    u8 value;
} State;

void func_080CE450(State *state, u8 value)
{
    state->value = value;
}
