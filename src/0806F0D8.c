#include "ffta.h"

/* 0x0806F0D8..0x0806F0DC: 4 bytes. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
} MenuState;

void func_0806F0D8(MenuState *state, u16 value)
{
    state->value = value;
}
