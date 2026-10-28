#include "ffta.h"

typedef struct {
    u8 unknown_00[7];
    u8 value;
} State08060450;

extern u8 func_080099A4(u8);

/* Complete [0x08060450, 0x08060468): 24 bytes, 11 instructions. */
u8 func_08060450(const State08060450 *state)
{
    if (func_080099A4(state->value) != 0)
        return 1;
    return 0;
}
