#include "ffta.h"

/* 0x080CE428..0x080CE42E: 6 bytes. */
typedef struct {
    u8 unknown_00[0xDA];
    u8 value;
} State;

void func_080CE428(State *state, u8 value)
{
    state->value = value;
}
