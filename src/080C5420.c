#include "ffta.h"

/* 0x080C5420..0x080C5426: 6 bytes. */
typedef struct {
    u8 unknown_00[0x1C];
    u8 first;
    u8 second;
} State;

void func_080C5420(State *state, u8 first, u8 second)
{
    state->first = first;
    state->second = second;
}
