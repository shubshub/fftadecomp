#include "ffta.h"

/* 0x080DD494..0x080DD4A2: 14 bytes / 6 instructions. */
struct SelectionState;

extern u8 func_080A8830(const struct SelectionState *state);

u8 func_080DD494(const struct SelectionState *state)
{
    return func_080A8830(state);
}
